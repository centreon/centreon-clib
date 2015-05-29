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
launch_specification::security_group::security_group() {
  _init_bindings();
}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
launch_specification::security_group::security_group(
  launch_specification::security_group const& other)
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
launch_specification::security_group&
  launch_specification::security_group::operator=(
    launch_specification::security_group const& other) {
  if (this != &other) {
    group_name = other.group_name;
    group_id = other.group_id;
  }
  return (*this);
}

/**
 *  Destructor.
 */
launch_specification::security_group::~security_group() {

}

/**
 *  Init the bindings.
 */
void launch_specification::security_group::_init_bindings() {
  add_member("GroupName", group_name);
  add_member("GroupId", group_id);
}

/**
 *  Default constructor.
 */
launch_specification::iam::iam() {
  _init_bindings();
}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
launch_specification::iam::iam(launch_specification::iam const& other)
  : instance_profile_arn(other.instance_profile_arn),
    instance_profile_name(other.instance_profile_name) {
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this object.
 */
launch_specification::iam& launch_specification::iam::operator=(
  launch_specification::iam const& other) {
  if (this != &other) {
    instance_profile_arn = other.instance_profile_arn;
    instance_profile_name = other.instance_profile_name;
  }
  return (*this);
}

/**
 *  Destructor.
 */
launch_specification::iam::~iam() {

}

/**
 *  Is this object null?
 *
 *  @return  True if this object is null.
 */
bool launch_specification::iam::is_null() const {
  return (instance_profile_arn.empty() && instance_profile_name.empty());
}

/**
 *  Init the bindings.
 */
void launch_specification::iam::_init_bindings() {
  add_member("InstanceProfileArn", instance_profile_arn);
  add_member("InstanceProfileName", instance_profile_name);
}

/**
 *  Default constructor.
 */
launch_specification::monitoring::monitoring()
  : enabled(false) {

}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
launch_specification::monitoring::monitoring(
  launch_specification::monitoring const& other)
  : enabled(other.enabled) {

}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this object.
 */
launch_specification::monitoring& launch_specification::monitoring::operator=(
  launch_specification::monitoring const& other) {
  if (this != &other)
    enabled = other.enabled;
  return (*this);
}

/**
 *  Destructor.
 */
launch_specification::monitoring::~monitoring() {

}

/**
 *  Is this object null?
 *
 *  @return  True if this object is null.
 */
bool launch_specification::monitoring::is_null() const {
  return (enabled == false);
}

/**
 *  Init the bindings.
 */
void launch_specification::monitoring::_init_bindings() {
  add_member("Enabled", enabled);
}

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
 *  Init the bindings.
 */
void launch_specification::_init_bindings() {
  add_member("ImageId", _image_id);
  add_member("KeyName", _key_name);
  add_member("SecurityGroups", _security_groups);
  add_member("UserData", _user_data);
  add_member("InstanceType", _instance_type);
  add_member("PlacementAvailabilityZone", _placement_availability_zone);
  add_member("PlacementGroupName", _placement_group_name);
  add_member("KernelId", _kernel_id);
  add_member("RamdiskId", _ramdisk_id);
  add_member("SubnetId", _subnet_id);
  add_member("NetworkInterfaces", _network_interfaces);
  add_member("Iam", _iam);
  add_member("EbsOptimized", _ebs_optimized);
  add_member("Monitoring", _monitoring);
}

/**
 *  Copy an object.
 *
 *  @param[in] other  The object to copy.
 */
void launch_specification::_internal_copy(launch_specification const& other) {
  _image_id = other._image_id;
  _key_name = other._key_name;
  _security_groups = other._security_groups;
  _user_data = other._user_data;
  _instance_type = other._instance_type;
  _placement_availability_zone = other._placement_availability_zone;
  _placement_group_name = other._placement_group_name;
  _kernel_id = other._kernel_id;
  _ramdisk_id = other._kernel_id;
  _block_device_mappings = other._block_device_mappings;
  _subnet_id = other._subnet_id;
  _network_interfaces = other._network_interfaces;
  _iam = other._iam;
  _ebs_optimized = other._ebs_optimized;
  _monitoring = other._monitoring;
}
