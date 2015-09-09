/*
** Copyright 2011-2014 Centreon
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

#include "com/centreon/aws/ec2/spot_instance_fault.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
spot_instance_fault::spot_instance_fault() {
  _init_bindings();
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
spot_instance_fault::spot_instance_fault(spot_instance_fault const& other)
  : json::json_serializable(other){
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
 *  Init the serialization binding.
 */
void spot_instance_fault::_init_bindings() {
  add_member("Code", _code);
  add_member("Message", _message);
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
