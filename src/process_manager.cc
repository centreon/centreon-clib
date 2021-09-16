/*
** Copyright 2012-2013, 2021 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#include "com/centreon/process_manager.hh"
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/logging/logger.hh"
#include "com/centreon/process_listener.hh"

using namespace com::centreon;

// Default varibale.
static int const DEFAULT_TIMEOUT = 200;

/**
 *  Default constructor. It is private. No need to call, we just use the static
 *  internal function instance().
 */
process_manager::process_manager() : _update{true}, _running{false} {
  std::unique_lock<std::mutex> lck(_running_m);
  _thread = std::thread(&process_manager::_run, this);
  pthread_setname_np(_thread.native_handle(), "clib_prc_mgr");
  _running_cv.wait(lck, [this]() -> bool { return _running; });
}

/**
 *  Destructor.
 */
process_manager::~process_manager() noexcept {
  // Kill all running process.
  {
    shared_lock lock(_pid_m);
    assert(_processes_pid.size() == 0);
    for (auto it = _processes_pid.begin(), end = _processes_pid.end();
         it != end; ++it) {
      try {
        it->second->kill();
      } catch (const std::exception& e) {
        (void)e;
      }
    }
  }

  // Waiting the end of the process manager thread.
  _running = false;
  _thread.join();

  // Waiting all process.
  int status = 0;
  auto time_limit =
      std::chrono::system_clock::now() + std::chrono::seconds(10);
  int ret = ::waitpid(-1, &status, WNOHANG);
  while (ret >= 0 || (ret < 0 && errno == EINTR)) {
    if (ret == 0)
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ret = ::waitpid(-1, &status, WNOHANG);
    if (std::chrono::system_clock::now() >= time_limit)
      break;
  }
}

/**
 *  Add a process to the process manager.
 *
 *  @param[in] p    The process to manage.
 *  @param[in] obj  The object to notify.
 */
void process_manager::add(process* p) {
  // Check viability pointer.
  assert(p);

  // We lock _lock_processes before to avoid deadlocks
  {
    std::lock_guard<shared_mutex> lck(_fds_m);

    // Monitor err/out output if necessary.
    if (p->_enable_stream[process::out]) {
      _processes_fd[p->_stream[process::out]] = p;
      _fds.push_back(
          {p->_stream[process::out], POLLIN | POLLPRI | POLL_HUP, 0});
    }
    if (p->_enable_stream[process::err]) {
      _processes_fd[p->_stream[process::err]] = p;
      _fds.push_back(
          {p->_stream[process::err], POLLIN | POLLPRI | POLL_HUP, 0});
    }
  }
  std::lock_guard<std::mutex> lock(_lock_processes);
  // Add timeout to kill process if necessary.
  if (p->_timeout)
    _processes_timeout.insert({p->_timeout, p});

  // Need to update file descriptor list.
  //_update = true;

  // Add pid process to use waitpid.
  {
    std::lock_guard<shared_mutex> lck(_pid_m);
    _processes_pid[p->_process] = p;
  }
}

/**
 *  Get instance of the process manager.
 *
 *  @return the process manager.
 */
process_manager& process_manager::instance() {
  static process_manager instance;
  return instance;
}

/**
 *  close syscall wrapper.
 *
 *  @param[in, out] fd The file descriptor to close.
 */
void process_manager::_close(int& fd) noexcept {
  if (fd >= 0) {
    while (::close(fd) < 0 && errno == EINTR)
      std::this_thread::yield();
  }
  fd = -1;
}

/**
 *  Close stream.
 *
 *  @param[in] fd  The file descriptor to close.
 */
void process_manager::_close_stream(int fd) noexcept {
  try {
    process* p;
    // Get process to link with fd and remove this
    // fd to the process manager.
    {
      _update = true;
      std::unordered_map<int, process*>::iterator it(_processes_fd.find(fd));
      if (it == _processes_fd.end())
        throw basic_error() << "invalid fd: not found in processes fd list";

      p = it->second;
      _processes_fd.erase(it);
    }

    // Update process informations.
    p->do_close(fd);
  } catch (const std::exception& e) {
    log_error(logging::high) << e.what();
  }
}

/**
 *  Remove process from list of processes timeout.
 *
 *  @param[in] p The process to remove.
 */
void process_manager::_erase_timeout(process* p) {
  // Check process viability.
  if (!p || !p->_timeout)
    return;
  std::lock_guard<std::mutex> lock(_lock_processes);
  auto range = _processes_timeout.equal_range(p->_timeout);
  for (auto it = range.first; it != range.second; ++it) {
    if (it->second == p) {
      _processes_timeout.erase(it);
      break;
    }
  }
}

/**
 *  Kill process to reach the timeout.
 */
void process_manager::_kill_processes_timeout() noexcept {
  std::lock_guard<std::mutex> lock(_lock_processes);
  // Get the current time.
  std::time_t now(time(nullptr));

  // Kill process who timeout and remove it from timeout list.
  for (auto it = _processes_timeout.begin(), end = _processes_timeout.end();
       it != end && it->first <= now;) {
    process* p = it->second;
    try {
      p->kill();
    } catch (const std::exception& e) {
      log_error(logging::high) << e.what();
    }
    it = _processes_timeout.erase(it);
  }
}

/**
 *  Read stream.
 *
 *  @param[in] fd  The file descriptor to read.
 *
 *  @return Number of bytes read.
 */
uint32_t process_manager::_read_stream(int fd) noexcept {
  uint32_t size(0);
  try {
    process* p;
    // Get process to link with fd.
    {
      shared_lock lock(_fds_m);
      auto it = _processes_fd.find(fd);
      if (it == _processes_fd.end()) {
        _update = true;
        throw basic_error() << "invalid fd: not found in processes fd list";
      }
      p = it->second;
    }

    size = p->do_read(fd);
  } catch (const std::exception& e) {
    log_error(logging::high) << e.what();
  }
  return size;
}

/**
 *  Internal thread to monitor processes.
 */
void process_manager::_run() {
  {
    std::lock_guard<std::mutex> lck(_running_m);
    _fds.reserve(64);
    _running = true;
    _running_cv.notify_all();
  }
  try {
    for (;;) {
      // Update the file descriptor list.
      if (_update)
        _update_list();

      shared_lock lck(_fds_m);
      {
        shared_lock lck(_pid_m);
        if (!_running && _fds.size() == 0 && _processes_pid.size() == 0 &&
            _orphans_pid.size() == 0)
          break;
      }

      assert(_processes_fd.size() == _fds.size());
      int ret = poll(_fds.data(), _fds.size(), DEFAULT_TIMEOUT);
      if (ret < 0) {
        if (errno == EINTR)
          ret = 0;
        else {
          const char* msg = strerror(errno);
          throw basic_error() << "poll failed: " << msg;
        }
      }
      for (uint32_t i = 0, checked = 0;
           checked < static_cast<uint32_t>(ret) && i < _fds.size(); ++i) {
        // No event.
        if (!_fds[i].revents)
          continue;

        ++checked;

        // Data are available.
        uint32_t size = 0;
        if (_fds[i].revents & (POLLIN | POLLPRI))
          size = _read_stream(_fds[i].fd);
        // File descriptor was close.
        if ((_fds[i].revents & POLLHUP) && !size)
          _close_stream(_fds[i].fd);

        //  Error!
        else if (_fds[i].revents & (POLLERR | POLLNVAL)) {
          _update = true;
          log_error(logging::high)
              << "invalid fd " << _fds[i].fd << " from process manager";
        }
      }
      // Release finished process.
      _wait_processes();
      _wait_orphans_pid();
      // Kill process in timeout.
      _kill_processes_timeout();
    }
  } catch (const std::exception& e) {
    log_error(logging::high) << e.what();
  }
}

/**
 *  Update process informations at the end of the process.
 *
 *  @param[in] p       The process to update informations.
 *  @param[in] status  The status of the process to set.
 */
void process_manager::_update_ending_process(process* p, int status) noexcept {
  // Check process viability.
  if (!p)
    return;

  p->update_ending_process(status);
  _erase_timeout(p);
}

/**
 *  Update list of file descriptors to watch.
 */
void process_manager::_update_list() {
  std::lock_guard<shared_mutex> lck(_fds_m);
  // Set file descriptor to wait event.
  if (_processes_fd.size() != _fds.size())
    _fds.resize(_processes_fd.size());

  auto itt = _fds.begin();
  for (auto it = _processes_fd.begin(), end = _processes_fd.end(); it != end;
       ++it) {
    itt->fd = it->first;
    itt->events = POLLIN | POLLPRI | POLL_HUP;
    itt->revents = 0;
    ++itt;
  }
  // Disable update.
  _update = false;
}

/**
 *  Waiting orphans pid.
 */
void process_manager::_wait_orphans_pid() noexcept {
  try {
    std::lock_guard<shared_mutex> lock(_pid_m);
    std::deque<orphan>::iterator it = _orphans_pid.begin();
    while (it != _orphans_pid.end()) {
      // Get process to link with pid and remove this pid
      // to the process manager.
      auto it_p = _processes_pid.find(it->pid);
      if (it_p == _processes_pid.end()) {
        ++it;
        continue;
      }
      process* p = it_p->second;
      _processes_pid.erase(it_p);

      // Update process.
      _update_ending_process(p, it->status);

      // Erase orphan pid.
      it = _orphans_pid.erase(it);
    }
  } catch (const std::exception& e) {
    log_error(logging::high) << e.what();
  }
}

/**
 *  Waiting finished process.
 */
void process_manager::_wait_processes() noexcept {
  try {
    for (;;) {
      int status = 0;
      assert(_processes_fd.size() <= _fds.size());
      pid_t pid(::waitpid(-1, &status, WNOHANG));
      // No process are finished.
      if (pid <= 0)
        break;

      process* p = nullptr;
      // Get process to link with pid and remove this pid
      // to the process manager.
      {
        std::lock_guard<shared_mutex> lock(_pid_m);
        auto it = _processes_pid.find(pid);
        if (it == _processes_pid.end()) {
          _orphans_pid.emplace_back(pid, status);
          continue;
        }
        p = it->second;
        _processes_pid.erase(it);
      }

      // Update process.
      if (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL)
        p->set_timeout(true);
      _update_ending_process(p, status);
    }
  } catch (const std::exception& e) {
    log_error(logging::high) << e.what();
  }
}
