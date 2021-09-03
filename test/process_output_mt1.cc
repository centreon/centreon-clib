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
#include <future>
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
  int ret(EXIT_SUCCESS);
  try {
    if (argc != 2 || (strcmp(argv[1], "err") && strcmp(argv[1], "out"))) {
      std::cerr << "usage: " << argv[0] << " err|out" << std::endl;
      return EXIT_FAILURE;
    }

    std::string cmd("./bin_test_process_output check_output ");
    cmd += argv[1];

    /* out or err? */
    bool out = !strcmp(argv[1], "out");

    static constexpr size_t size = 10 * 1024;
    static constexpr size_t count = 30;

    process p;
    std::promise<bool> prm;
    std::future<bool> running = prm.get_future();
    std::thread th_exec([&p, &cmd, &prm] {
      p.exec(cmd);
      prm.set_value(true);
    });

    running.get();

    char buffer_write[size + 1];
    buffer_write[size] = 0;
    for (unsigned int i = 0; i < size; ++i)
      buffer_write[i] = static_cast<char>('A' + i % 26);

    for (int i = 0; i < count; i++) {
      unsigned int total_write = 0;
      do {
        if (total_write < size)
          total_write +=
              p.write(buffer_write + total_write, size - total_write);
      } while (total_write < size);
    }

    std::cout << "W ";
    for (int i = 0; i < count; i++)
      std::cout << buffer_write;
    std::cout << std::endl;

    std::thread th_read([&p, &out] {
      std::string buffer_read;
      do {
        std::string data;
        if (out)
          p.read(data);
        else
          p.read_err(data);
        buffer_read += data;
      } while (buffer_read.size() < size * count);

      std::cout << "R " << buffer_read << std::endl;
      for (int i = 0, j = 0; i < size * count; i++) {
        if (static_cast<char>('A' + j % 26) != buffer_read[i])
          throw basic_error() << "Bad character read in data at position " << i;
        if (++j == size)
          j = 0;
      }
    });

    th_exec.join();
    th_read.join();
    p.update_ending_process(0);
    p.wait();

    if (p.exit_code() != EXIT_SUCCESS)
      throw basic_error() << "invalid return";
  } catch (std::exception const& e) {
    ret = EXIT_FAILURE;
    std::cerr << "error: " << e.what() << std::endl;
  }
  return ret;
}
