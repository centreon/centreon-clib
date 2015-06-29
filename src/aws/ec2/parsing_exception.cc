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

#include "com/centreon/aws/ec2/parsing_exception.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
parsing_exception::parsing_exception() {

}

/**
 *  Copy constructor.
 *
 *   @param[in] other  The object to copy.
 */
parsing_exception::parsing_exception(
                     parsing_exception const& other)
  : exceptions::basic(other) {
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this object.
 */
parsing_exception& parsing_exception::operator=(
                     parsing_exception const& other) {
  exceptions::basic::operator=(other);
  return (*this);
}

/**
 *  Destructor.
 */
parsing_exception::~parsing_exception() throw() {

}
