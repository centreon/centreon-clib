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

#include "com/centreon/aws/ec2/launch_specification.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
launch_specification::launch_specification()
  : _ebs_optimized(false) {

}

/**
 *  Destructor.
 */
launch_specification::~launch_specification() {

}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
launch_specification::launch_specification(
                        launch_specification const& other) {
  _internal_copy(other);
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           A reference to this object.
 */
launch_specification& launch_specification::operator=(
                        launch_specification const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Copy an object.
 *
 *  @param[in] other  The object to copy.
 */
void launch_specification::_internal_copy(launch_specification const& other) {

}
