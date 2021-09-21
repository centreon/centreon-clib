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
#include <cstring>
#include <iostream>
#include <string>
#include "com/centreon/clib.hh"
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/process.hh"

using namespace com::centreon;

/**
 *  Check class process (read stdout/stderr).
 *
 *  @return EXIT_SUCCESS on success.
 */
int main(int argc, char** argv) {
  constexpr int size = 10 * 1024;

  int ret(EXIT_SUCCESS);
  try {
    if (argc != 2 || (strcmp(argv[1], "err") && strcmp(argv[1], "out"))) {
      std::cerr << "usage: " << argv[0] << " err|out" << std::endl;
      return (EXIT_FAILURE);
    }

    std::string cmd("./bin_test_process_output check_output ");
    cmd += argv[1];

    process p;
    p.exec(cmd);
    char buffer_write[size];
    std::string buffer_read;
    for (size_t i = 0; i < sizeof(buffer_write); ++i)
      buffer_write[i] = 'A' + i / 4096;
    buffer_write[size - 1] = 0;
    size_t total_read = 0;
    size_t total_write = 0;
    do {
      std::string tmp;
      if (total_write < sizeof(buffer_write))
        total_write += p.write(buffer_write + total_write,
                               sizeof(buffer_write) - total_write);
      if (!strcmp(argv[1], "out"))
        p.read(tmp);
      else
        p.read_err(tmp);
      total_read += tmp.size();
      buffer_read.append(tmp);
    } while (total_read < sizeof(buffer_write));
    p.kill(SIGTERM);
    p.wait();
    if (p.exit_code() != EXIT_SUCCESS)
      throw basic_error() << "invalid return";
    if (total_write != sizeof(buffer_write))
      throw basic_error() << "invalid data write";
    if (total_write != total_read)
      throw basic_error() << "invalid data read";
    if (memcmp(buffer_write, buffer_read.data(), total_read) != 0)
      throw basic_error() << "bad copy";
  } catch (std::exception const& e) {
    ret = EXIT_FAILURE;
    std::cerr << "error: " << e.what() << std::endl;
  }
  return ret;
}
