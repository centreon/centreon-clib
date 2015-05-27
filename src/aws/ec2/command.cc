/*
** Copyright 2011-2014 Merethis
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

#include "com/centreon/process.hh"
#include "com/centreon/aws/ec2/command.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Constructor.
 *
 *  @param[in] profile  The name of the profile that should be
 *                      used by the aws cli wrapper.
 */
command::command(std::string const& profile)
  : _profile(profile) {
  _sanity_checks();
}

/**
 *  Destructor.
 */
command::~command() {

}

/**
 *  Check that aws cli exists.
 */
void command::_sanity_checks() {
  process proc;
  proc.exec("aws help", _command_timeout);
  proc.wait();
  if (proc.exit_status() != process::normal || proc.exit_code() != 0) {
    std::string err;
    proc.read_err(err);
    throw (exceptions::basic() << "couldn't execute aws: " << err);
  }
}
