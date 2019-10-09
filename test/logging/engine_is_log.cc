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

#include <iostream>
#include <memory>
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/logging/engine.hh"
#include "./backend_test.hh"

using namespace com::centreon::logging;

/**
 *  Check is log.
 *
 *  @return 0 on success.
 */
int main() {
  int retval;
  engine::load();
  try {
    engine& e(engine::instance());
    std::unique_ptr<backend_test> obj(new backend_test);

    uint32_t limits(sizeof(uint32_t) * CHAR_BIT);
    for (uint32_t i(0); i < 3; ++i) {
      for (uint32_t j(0); j < limits; ++j) {
        unsigned long id(e.add(obj.get(), 1 << j, i));
        for (uint32_t k(0); k < limits; ++k) {
          if (e.is_log(1 << k, i) != (k == j))
            throw(basic_error() << "is log failed with types(" << j
                                << ") verbose(" << i << ")");

          for (uint32_t k(0); k < 3; ++k) {
            if (e.is_log(1 << j, k) != (i >= k))
              throw(basic_error() << "is log failed with types(" << j
                                  << ") verbose(" << i << ")");
          }
        }
        if (!e.remove(id))
          throw(basic_error() << "remove id failed");
      }
    }
    retval = 0;
  }
  catch (std::exception const& e) {
    std::cerr << "error: " << e.what() << std::endl;
    retval = 1;
  }
  engine::unload();
  return (retval);
}
