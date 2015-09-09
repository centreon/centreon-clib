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

#include <cstdlib>
#include <iostream>
#include "com/centreon/clib.hh"
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/process.hh"

using namespace com::centreon;

/**
 *  Check class process (wait timeout).
 *
 *  @return EXIT_SUCCESS on success.
 */
int main() {
  int ret(EXIT_SUCCESS);
  clib::load();
  try {
    process p;
    p.exec("./bin_test_process_output check_sleep 1");
    if (p.wait(500) == true)
      throw (basic_error() << "wait timeout failed: "
             "waiting more than necessary");
    if (p.wait(1500) == false)
      throw (basic_error() << "wait timeout failed: "
             "waiting less than necessary");
  }
  catch (std::exception const& e) {
    ret = EXIT_FAILURE;
    std::cerr << "error: " << e.what() << std::endl;
  }
  clib::unload();
  return (ret);
}
