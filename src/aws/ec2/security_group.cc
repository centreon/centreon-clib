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
  : group_name(other.group_name),
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
  json::serialize(group_name, writer);
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
