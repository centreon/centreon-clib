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

#include <cstring>
#include "com/centreon/aws/ec2/security_group.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon;
using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
security_group::security_group() {
  _init_bindings();
}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
security_group::security_group(security_group const& other)
  : json::json_serializable(other),
    group_name(other.group_name),
    group_id(other.group_id) {
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this object.
 */
security_group& security_group::operator=(security_group const& other) {
  if (this != &other) {
    group_name = other.group_name;
    group_id = other.group_id;
  }
  return (*this);
}

/**
 *  Destructor.
 */
security_group::~security_group() {

}

/**
 *  Get the group name.
 *
 *  @return  The group name.
 */
std::string const& security_group::get_group_name() const throw() {
  return (group_name);
}

/**
 *  Get the group id.
 *
 *  @return  The group id.
 */
std::string const& security_group::get_group_id() const throw() {
  return (group_id);
}

/**
 *  Set the group name.
 *
 *  @param[in] val  The new group name.
 */
void security_group::set_group_name(std::string const& val) {
  group_name = val;
}

/**
 *  Set the group id.
 *
 *  @param[in] val  The new group id.
 */
void security_group::set_group_id(std::string const& val) {
  group_id = val;
}

/**
 *  Serialize the security group.
 *
 *  @param[in] writer  Writer.
 */
void security_group::serialize(json::json_writer& writer) const {
  if (!group_name.empty())
    json::serialize(group_name, writer);
  else if (!group_id.empty())
    json::serialize(group_id, writer);
}

/**
 *  Init the bindings.
 */
void security_group::_init_bindings() {
  add_member(
    "GroupName",
    group_name);
  add_member(
    "GroupId",
    group_id);
}
