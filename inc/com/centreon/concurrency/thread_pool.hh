/*
** Copyright 2011-2013 Centreon
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

#ifndef CC_CONCURRENCY_THREAD_POOL_HH
#define CC_CONCURRENCY_THREAD_POOL_HH

#include <condition_variable>
#include <list>
#include <mutex>
#ifndef _WIN32
#include <sys/types.h>
#endif  // POSIX
#include "com/centreon/namespace.hh"
#include "com/centreon/concurrency/runnable.hh"
#include "com/centreon/concurrency/thread.hh"

CC_BEGIN()

namespace concurrency {
/**
 *  @class thread_pool thread_pool.hh "com/centreon/concurrency/thread_pool.hh"
 *  @brief Allow to manage a collection of threads.
 *
 *  Allow to manage a collection of thread and reduce cost of lunching
 *  thread by recycle threads.
 */
class thread_pool {
  class internal_thread : public thread {
    bool _quit;
    thread_pool* _th_pool;

    internal_thread(internal_thread const& right);
    internal_thread& operator=(internal_thread const& right);
    internal_thread& _internal_copy(internal_thread const& right);
    void _run();

   public:
    internal_thread(thread_pool* th_pool);
    ~internal_thread() noexcept;
    void quit();
  };

  std::condition_variable _cnd_pool;
  std::condition_variable _cnd_thread;
  uint32_t _current_task_running;
  uint32_t _max_thread_count;
  mutable std::mutex _mtx_pool;
  mutable std::mutex _mtx_thread;
#ifndef _WIN32
  pid_t _pid;
#endif  // POSIX
  std::list<internal_thread*> _pool;
  bool _quit;
  std::list<runnable*> _tasks;

  thread_pool(thread_pool const& right);
  thread_pool& operator=(thread_pool const& right);

 public:
  thread_pool(uint32_t max_thread_count = 0);
  ~thread_pool() noexcept;
  uint32_t get_current_task_running() const noexcept;
  uint32_t get_max_thread_count() const noexcept;
  void set_max_thread_count(uint32_t max);
  void start(runnable* r);
  void wait_for_done();
};
}

CC_END()

#endif  // !CC_CONCURRENCY_THREAD_POOL_HH
