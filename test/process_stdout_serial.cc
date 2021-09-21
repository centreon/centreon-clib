/*
** Copyright 2021 Centreon
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
#include <cstring>
#include <iostream>
#include "com/centreon/clib.hh"
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/process.hh"

using namespace com::centreon;

/**
 *  Check class process (environement).
 *
 *  @return EXIT_SUCCESS on success.
 */
int main() {
  constexpr int count = 10;
  int sum = 0;
  int ret(EXIT_SUCCESS);
  try {
    for (int i = 0; i < count; i++) {
      process p(nullptr, false, true, false);
      p.exec("./bin_test_process_output check_stdout 0");
      std::string output;
      p.read(output);
      p.wait();
      sum += strcmp(output.c_str(), "check_stdout\n");
    }
    if (sum != 0)
      throw basic_error() << "check environment failed";
  } catch (std::exception const& e) {
    ret = EXIT_FAILURE;
    std::cerr << "error: " << e.what() << std::endl;
  }
  return ret;
}
