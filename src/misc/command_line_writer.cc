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

#include <cctype>
#include <cstring>
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/misc/command_line_writer.hh"

using namespace com::centreon::misc;

/**
 *  Default constructor.
 */
command_line_writer::command_line_writer() {

}

/**
 *  Constructor.
 *
 *  @param[in] cmd  The start of the command to call.
 */
command_line_writer::command_line_writer(std::string const& cmd) {
  _command_line = cmd;
  _command_line.push_back(' ');
}

/**
 *  Copy constructor.
 *
 *  @param[in] right  Command line writer to copy.
 */
command_line_writer::command_line_writer(command_line_writer const& right) {
  _command_line = right._command_line;
}

/**
 *  Destructor.
 */
command_line_writer::~command_line_writer() throw () {

}

/**
 *  Assignment operator.
 *
 *  @param[in] right  Object to copy.
 *
 *  @return           Reference to this object.
 */
command_line_writer& command_line_writer::operator=(command_line_writer const& right) {
  if (this != &right)
    _command_line = right._command_line;
  return (*this);
}

/**
 *  Get the command built.
 *
 *  @return  The build command.
 */
std::string const& command_line_writer::get_command() const throw() {
  return (_command_line);
}
