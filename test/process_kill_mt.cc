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
#include <thread>
#include <vector>
#include "com/centreon/clib.hh"
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/process.hh"
#include "com/centreon/timestamp.hh"

using namespace com::centreon;

/**
 *  Check class process (kill).
 *
 *  @return EXIT_SUCCESS on success.
 */
int main() {
  std::atomic_int sum{0};
  constexpr int count = 10;
  std::vector<std::thread> v;
  int ret = EXIT_SUCCESS;
  for (int i = 0; i < count; i++) {
    v.emplace_back([&sum] {
      process p;
      p.exec("./bin_test_process_output check_sleep 1");
      p.kill();
      timestamp start(timestamp::now());
      p.wait();
      timestamp end(timestamp::now());
      sum += (end - start).to_seconds();
    });
  }

  for (auto& t : v)
    t.join();

  if (sum != 0) {
    std::cerr << "error: kill failed" << std::endl;
    ret = EXIT_FAILURE;
  }
  return ret;
}
