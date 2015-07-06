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
  : _ebs_optimized(false),
    _monitoring_enabled(false) {
  _init_bindings();
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
                        launch_specification const& other)
  : json::json_serializable(other) {
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
  if (this != &other) {
    json::json_serializable::operator=(other);
    _internal_copy(other);
  }
  return (*this);
}

/**
 *  Get the image id.
 *
 *  @return  The image id.
 */
std::string const& launch_specification::get_image_id() const throw() {
  return (_image_id);
}

/**
 *  Get the key name.
 *
 *  @return  The key name.
 */
std::string const& launch_specification::get_key_name() const throw() {
  return (_key_name);
}

/**
 *  Get the security groups.
 *
 *  @return  The security groups.
 */
std::vector<security_group> const&
  launch_specification::get_security_groups() const throw() {
  return (_security_groups);
}

/**
 *  Get the user data.
 *
 *  @return  The user data.
 */
std::string const& launch_specification::get_user_data() const throw() {
  return (_user_data);
}

/**
 *  Get the instance type.
 *
 *  @return  The instance type.
 */
std::string const& launch_specification::get_instance_type() const throw() {
  return (_instance_type);
}

/**
 *  Get the placement availability zone.
 *
 *  @return  The placement availability zone.
 */
std::string const& launch_specification::get_placement_availability_zone() const throw() {
  return (_placement_availability_zone);
}

/**
 *  Get the placement group name.
 *
 *  @return  The placement group name/
 */
std::string const& launch_specification::get_placement_group_name() const throw() {
  return (_placement_group_name);
}

/**
 *  Get the kernel id.
 *
 *  @return  The kernel id.
 */
std::string const& launch_specification::get_kernel_id() const throw() {
  return (_kernel_id);
}

/**
 *  Get the ramdisk id.
 *
 *  @return  The ramdisk id.
 */
std::string const& launch_specification::get_ramdisk_id() const throw() {
  return (_ramdisk_id);
}

/**
 *  Get the block device mappings.
 *
 *  @return  The block device mappings.
 */
std::vector<block_device_mapping> const& launch_specification::get_block_device_mappings() const throw() {
  return (_block_device_mappings);
}

/**
 *  Get the subnet id.
 *
 *  @return  The subnet id.
 */
std::string const& launch_specification::get_subnet_id() const throw() {
  return (_subnet_id);
}

/**
 *  Get the network interfaces.
 *
 *  @return  The newtork interfaces.
 */
std::vector<network_interface> const& launch_specification::get_network_interfaces() const throw() {
  return (_network_interfaces);
}

/**
 *  Get the IAM profile arn.
 *
 *  @return  The IAM profile arn.
 */
std::string const& launch_specification::get_iam_instance_profile_arn() const throw() {
  return (_iam_instance_profile_arn);
}

/**
 *  Get the IAM profile name.
 *
 *  @return  The IAM profile name.
 */
std::string const& launch_specification::get_iam_instance_profile_name() const throw() {
  return (_iam_instance_profile_name);
}

/**
 *  Get if the ebs should be optimized.
 *
 *  @return  True if the ebs should be optimized.
 */
bool launch_specification::get_ebs_optimized() const throw() {
  return (_ebs_optimized);
}

/**
 *  Get if the monitoring is enabled.
 *
 *  @return  True if the monitoring is enabled.
 */
bool launch_specification::get_monitoring_enabled() const throw() {
  return (_monitoring_enabled);
}

/**
 *  Set the image id.
 *
 *  @param[in] val  The new image id.
 */
void launch_specification::set_image_id(std::string const& val) {
  _image_id = val;
}

/**
 *  Set the key name.
 *
 *  @param[in] val  The new key name.
 */
void launch_specification::set_key_name(std::string const& val) {
  _key_name = val;
}

/**
 *  Add a security group.
 *
 *  @param[in] val  The security group to add.
 */
void launch_specification::add_security_groups(security_group const& val) {
  _security_groups.push_back(val);
}

/**
 *  Set the user data.
 *
 *  @param[in] val  The new user data.
 */
void launch_specification::set_user_data(std::string const& val) {
  _user_data = val;
}

/**
 *  Set the instance type.
 *
 *  @param[in] val  The new instance type.
 */
void launch_specification::set_instance_type(std::string const& val) {
  _instance_type = val;
}

/**
 *  Set the placement availability zone.
 *
 *  @param[in] val  The new placement availability zone.
 */
void launch_specification::set_placement_availability_zone(std::string const& val) {
  _placement_availability_zone = val;
}

/**
 *  Set the placement group name.
 *
 *  @param[in] val  The new placement group name.
 */
void launch_specification::set_placement_group_name(std::string const& val) {
  _placement_group_name = val;
}

/**
 *  Set the kernel id.
 *
 *  @param[in] val  The new kernel id.
 */
void launch_specification::set_kernel_id(std::string const& val) {
  _kernel_id = val;
}

/**
 *  Set the ramdisk id.
 *
 *  @param[in] val  The new ramdisk id.
 */
void launch_specification::set_ramdisk_id(std::string const& val) {
  _ramdisk_id = val;
}

/**
 *  Add a new block device mapping.
 *
 *  @param[in] val  The new block device mapping.
 */
void launch_specification::add_block_device_mappings(block_device_mapping const& val) {
  _block_device_mappings.push_back(val);
}

/**
 *  Set the new subnet id.
 *
 *  @param[in] val  The new subnet id.
 */
void launch_specification::set_subnet_id(std::string const& val) {
  _subnet_id = val;
}

/**
 *  Add a new network interface.
 *
 *  @param[in] val  The new network interface.
 */
void launch_specification::add_network_interfaces(network_interface const& val) {
  _network_interfaces.push_back(val);
}

/**
 *  Set the IAM instance profile arn.
 *
 *  @param[in] val  The new IAM instance profile arn.
 */
void launch_specification::set_iam_instance_profile_arn(std::string const& val) {
  _iam_instance_profile_arn = val;
}

/**
 *  Set the iam instance profile name.
 *
 *  @param[in] val  The new IAM instance profile name.
 */
void launch_specification::set_iam_instance_profile_name(std::string const& val) {
  _iam_instance_profile_name = val;
}

/**
 *  Set if ebs optimized.
 *
 *  @param[in] val  True if ebs optimized.
 */
void launch_specification::set_ebs_optimized(bool val) {
  _ebs_optimized = val;
}

/**
 *  Set if monitoring enabled.
 *
 *  @param[in] val  True if monitoring enabled.
 */
void launch_specification::set_monitoring_enabled(bool val) {
  _monitoring_enabled = val;
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
  add_member("EbsOptimized", _ebs_optimized);
  json_serializable& iam = create_and_add_generic_sub_object("Iam");
  iam.add_member("InstanceProfileArn", _iam_instance_profile_arn);
  iam.add_member("InstanceProfileName", _iam_instance_profile_name);
  json_serializable& monitoring = create_and_add_generic_sub_object("Monitoring");
  monitoring.add_member("Enabled", _monitoring_enabled);
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
  _iam_instance_profile_arn = other._iam_instance_profile_arn;
  _iam_instance_profile_name = other._iam_instance_profile_name;
  _ebs_optimized = other._ebs_optimized;
  _monitoring_enabled = other._monitoring_enabled;
}
