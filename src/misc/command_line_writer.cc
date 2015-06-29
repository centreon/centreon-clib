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
