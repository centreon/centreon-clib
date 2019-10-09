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

#ifndef CC_LOGGING_ENGINE_HH
#define CC_LOGGING_ENGINE_HH

#include <climits>
#include <mutex>
#include <vector>
#include "com/centreon/namespace.hh"

CC_BEGIN()

namespace logging {
class backend;

/**
 *  @class engine engine.hh "com/centreon/logging/engine.hh"
 *  @brief Logging object manager.
 *
 *  This is an external access point to logging system. Allow to
 *  register backends and write log message into them.
 */
class engine {
  struct backend_info {
    unsigned long id;
    backend* obj;
    uint64_t types;
    uint32_t verbose;
  };

  std::vector<backend_info*> _backends;
  unsigned long _id;
  static engine* _instance;
  uint64_t _list_types[sizeof(uint32_t) * CHAR_BIT];
  mutable std::mutex _mtx;

  engine();
  engine(engine const& right);
  ~engine() throw();
  engine& operator=(engine const& right);
  void _rebuild_types();

 public:
  unsigned long add(backend* obj,
                    uint64_t types,
                    uint32_t verbose);
  /**
   *  Get the logger engine singleton.
   *
   *  @return The unique instance of logger engine.
   */
  static engine& instance() throw() { return (*_instance); }

  /**
   *  Check if at least one backend can log with this parameter.
   *
   *  @param[in] flag     The logging type to log.
   *  @param[in] verbose  The verbosity level.
   *
   *  @return True if at least one backend can log with this
   *          parameter, otherwise false.
   */
  bool is_log(uint64_t types, uint32_t verbose) const throw() {
    if (verbose >= sizeof(uint32_t) * CHAR_BIT)
      return (false);
    return (_list_types[verbose] & types);
  }
  static void load();
  void log(uint64_t types,
           uint32_t verbose,
           char const* msg,
           uint32_t size);
  bool remove(unsigned long id);
  uint32_t remove(backend* obj);
  void reopen();
  static void unload();
};
}

CC_END()

#endif  // !CC_LOGGING_ENGINE_HH
