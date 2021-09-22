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
#include <iostream>
#include <thread>
#include <vector>
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
  int ret = EXIT_SUCCESS;
  std::atomic_int sum{0};
  std::vector<std::thread> v;
  for (int i = 0; i < count; i++) {
    v.emplace_back([&sum] {
      process p;
      char* env[] = {(char*)"key1=value1", (char*)"key2=value2",
                     (char*)"key3=value3", NULL};
      p.exec(
          "./bin_test_process_output check_env "
          "key1=value1 key2=value2 key3=value3",
          env);
      p.wait();
      sum += p.exit_code();
    });
  }

  for (auto& t : v)
    t.join();

  if (sum != 0) {
    std::cerr << "error: check environment failed" << std::endl;
    ret = EXIT_FAILURE;
  }
  return ret;
}
