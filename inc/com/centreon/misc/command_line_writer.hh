/*
** Copyright 2011-2015 Centreon
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

#ifndef CC_MISC_COMMAND_LINE_WRITER_HH
#  define CC_MISC_COMMAND_LINE_WRITER_HH

#  include <string>
#  include <sstream>
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace         misc {
  /**
   *  @class command_line_writer command_line_writer.hh "com/centreon/misc/command_line_writer.hh"
   *  @brief Provide method to build a command line.
   *
   *  Command line writer is a simple writer for a command line.
   */
  class           command_line_writer {
  public:
                  command_line_writer();
                  command_line_writer(std::string const& cmd);
                  command_line_writer(command_line_writer const& right);
                  ~command_line_writer() throw ();
    command_line_writer&
                  operator=(command_line_writer const& right);

    template <typename T>
    /**
     *  Add an argument to the command line.
     *
     *  @param[in] arg_name  The argument name.
     *  @param[in] value     The argument value.
     *  @param[in] quoted    Should the argument be quoted?
     */
    void          add_arg(
                    std::string const& arg_name,
                    T const& value,
                    bool quoted = true) {
      std::ostringstream oss;
      oss << " " << arg_name << " ";
      if (quoted)
        oss << "\'";
      oss << value;
      if (quoted)
        oss << "\'";
      _command_line.append(oss.str());
    }

    template <typename T>
    /**
     *  Add an argument conditionally.
     *
     *  @param[in] arg_name   The argument name.
     *  @param[in] value      The argument value.
     *  @param[in] condition  True if the arugment should be added.
     *  @param[in] quoted     Should the argument be quoted?
     */
    void          add_arg_condition(
                    std::string const& arg_name,
                    T const& value,
                    bool condition,
                    bool quoted = true) {
      if (condition)
        add_arg(arg_name, value, quoted);
    }

    std::string const&
                  get_command() const throw();

  private:
    std::string   _command_line;
  };
}

CC_END()

#endif // !CC_MISC_COMMAND_LINE_WRITER_HH
