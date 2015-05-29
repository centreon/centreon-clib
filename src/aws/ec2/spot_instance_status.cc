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

#include "com/centreon/aws/ec2/spot_instance_status.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon;
using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
spot_instance_status::spot_instance_status() {
  _init_bindings();
}

/**
 *  Destructor.
 */
spot_instance_status::~spot_instance_status() {

}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
spot_instance_status::spot_instance_status(spot_instance_status const& other) {
  _internal_copy(other);
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference tot his object.
 */
spot_instance_status& spot_instance_status::operator=(
  spot_instance_status const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Get the update time of this instance.
 *
 *  @return  The update time of this instance.
 */
timestamp spot_instance_status::get_update_time() const {
  return (_update_time);
}

/**
 *  Get the code of this status.
 *
 *  @return  The code of this status.
 */
std::string const& spot_instance_status::get_code() const {
  return (_code);
}

/**
 *  Get the message of this status.
 *
 *  @return  The message of this status.
 */
std::string const& spot_instance_status::get_message() const {
  return (_message);
}

/**
 *  Set the update time of this instance.
 *
 *  @param[in] update  The update time of this instance.
 */
void spot_instance_status::set_update_time(std::string const& update) {
  _update_time = timestamp::from_utc(update);
}

/**
 *  Set the code of this status.
 *
 *  @param[in] code  The code of this status.
 */
void spot_instance_status::set_code(std::string const& code) {
  _code = code;
}

/**
 *  Set the message of this status.
 *
 *  @param[in] message  The message of this status.
 */
void spot_instance_status::set_message(std::string const& message) {
  _message = message;
}

/**
 *  Is this status null?
 *
 *  @return  True if this status is null.
 */
bool spot_instance_status::is_null() const {
  return (_update_time.is_null() && _code.empty() && _message.empty());
}

/**
 *  Init serialization bindings.
 */
void spot_instance_status::_init_bindings() {
  add_member("UpdateTime", _update_time);
  add_member("Message", _message);
  add_member("Code", _code);
}

/**
 *  Copy an object.
 *
 *  @param[in] other  The object to copy.
 */
void spot_instance_status::_internal_copy(spot_instance_status const& other) {
  _update_time = other._update_time;
  _code = other._code;
  _message = other._message;
}
