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

#include "com/centreon/aws/ec2/spot_instance_fault.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
spot_instance_fault::spot_instance_fault() {

}

/**
 *  Destructor.
 */
spot_instance_fault::~spot_instance_fault() {

}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
spot_instance_fault::spot_instance_fault(spot_instance_fault const& other) {
  _internal_copy(other);
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference tot his object.
 */
spot_instance_fault& spot_instance_fault::operator=(spot_instance_fault const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Get the code of this fault.
 *
 *  @return  The code of this fault.
 */
std::string const& spot_instance_fault::get_code() const {
  return (_code);
}

/**
 *  Get the message of this fault.
 *
 *  @return  The message of this fault.
 */
std::string const& spot_instance_fault::get_message() const {
  return (_message);
}

/**
 *  Set the code of this fault.
 *
 *  @param[in] code  The code of this fault.
 */
void spot_instance_fault::set_code(std::string const& code) {
  _code = code;
}

/**
 *  Set the message of this fault.
 *
 *  @param[in] message  The message of this fault.
 */
void spot_instance_fault::set_message(std::string const& message) {
  _message = message;
}

/**
 *  Is this fault null?
 *
 *  @return  True if this fault is null.
 */
bool spot_instance_fault::is_null() const {
  return (_code.empty() && _message.empty());
}

/**
 *  Copy an object.
 *
 *  @param[in] other  The object to copy.
 */
void spot_instance_fault::_internal_copy(spot_instance_fault const& other) {
  _code = other._code;
  _message = other._message;
}
