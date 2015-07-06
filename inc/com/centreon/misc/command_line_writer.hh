/*
** Copyright 2011-2015 Merethis
**
** This file is part of Centreon Clib.
**
** Centreon Clib is free software: you can redistribute it
** and/or modify it under the terms of the GNU Affero General Public
** License as published by the Free Software Foundation, either version
** 3 of the License, or (at your option) any later version.
**
** Centreon Clib is distributed in the hope that it will be
** useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Affero General Public License for more details.
**
** You should have received a copy of the GNU Affero General Public
** License along with Centreon Clib. If not, see
** <http://www.gnu.org/licenses/>.
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
