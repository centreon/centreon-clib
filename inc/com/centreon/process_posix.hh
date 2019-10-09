/*
** Copyright 2012-2013 Centreon
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

#ifndef CC_PROCESS_POSIX_HH
#define CC_PROCESS_POSIX_HH

#include <condition_variable>
#include <mutex>
#include <string>
#include <sys/types.h>
#include "com/centreon/namespace.hh"
#include "com/centreon/timestamp.hh"

CC_BEGIN()

class process_listener;
class process_manager;

/**
 *  @class process process_posix.hh "com/centreon/process_posix.hh"
 *  @brief Process execution class.
 *
 *  Execute external process.
 */
class process {
  friend class process_manager;

  process(process const& p);
  process& operator=(process const& p);
  static void _close(int& fd) throw();
  static pid_t _create_process_with_setpgid(char** args, char** env);
  static pid_t _create_process_without_setpgid(char** args, char** env);
  static void _dev_null(int fd, int flags);
  static int _dup(int oldfd);
  static void _dup2(int oldfd, int newfd);
  bool _is_running() const throw();
  void _kill(int sig);
  static void _pipe(int fds[2]);
  uint32_t _read(int fd, void* data, uint32_t size);
  static void _set_cloexec(int fd);

  std::string _buffer_err;
  std::string _buffer_out;
  pid_t (*_create_process)(char**, char**);
  mutable std::condition_variable _cv_buffer_err;
  mutable std::condition_variable _cv_buffer_out;
  mutable std::condition_variable _cv_process;
  bool _enable_stream[3];
  timestamp _end_time;
  bool _is_timeout;
  process_listener* _listener;
  mutable std::mutex _lock_process;
  pid_t _process;
  timestamp _start_time;
  int _status;
  int _stream[3];
  uint32_t _timeout;

 public:
  enum status {
    normal = 0,
    crash = 1,
    timeout = 2
  };
  enum stream {
    in = 0,
    out = 1,
    err = 2
  };

  process(process_listener* l = NULL);
  virtual ~process() throw();
  void enable_stream(stream s, bool enable);
  timestamp const& end_time() const throw();
  void exec(char const* cmd, char** env = NULL, uint32_t timeout = 0);
  void exec(std::string const& cmd, uint32_t timeout = 0);
  int exit_code() const throw();
  status exit_status() const throw();
  void kill();
  void read(std::string& data);
  void read_err(std::string& data);
  void setpgid_on_exec(bool enable) throw();
  bool setpgid_on_exec() const throw();
  timestamp const& start_time() const throw();
  void terminate();
  void wait() const;
  bool wait(unsigned long timeout) const;
  uint32_t write(std::string const& data);
  uint32_t write(void const* data, uint32_t size);
};

CC_END()

#endif  // !CC_PROCESS_POSIX_HH
