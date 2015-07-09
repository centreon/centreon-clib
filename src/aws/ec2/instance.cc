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

#include "com/centreon/aws/ec2/instance.hh"

using namespace com::centreon::aws::ec2;

static const char* instance_status_list[] =
  {"pending",
   "running",
   "shutting-down",
   "terminated",
   "stopping",
   "stopped",
   "rebooting"};

instance::product_code::product_code() {
  _init_bindings();
}

instance::product_code::product_code(product_code const& other)
  : json_serializable(other){
  _product_code_id = other._product_code_id;
  _product_code_type = other._product_code_type;
  _init_bindings();
}

instance::product_code&
  instance::product_code::operator=(product_code const& other) {
  if (this != &other) {
    json_serializable::operator=(other);
    _product_code_id = other._product_code_id;
    _product_code_type = other._product_code_type;
    _init_bindings();
  }
  return (*this);
}

instance::product_code::~product_code() {

}


void instance::product_code::_init_bindings() {
  add_member("ProductCodeId", _product_code_id);
  add_member("ProductCodeType", _product_code_type);
}

/**
 *  Default constructor.
 */
instance::instance()
  : _state_code(0),
    _ami_launch_index(0),
    _source_dest_check(false),
    _ebs_optimized(false) {
  _init_bindings();
}

/**
 *  Destructor.
 */
instance::~instance() {

}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
instance::instance(instance const& other)
  : json_serializable(other) {
  _internal_copy(other);
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return  Reference to this.
 */
instance& instance::operator=(instance const& other) {
  if (this != &other) {
    json_serializable::operator=(other);
    _internal_copy(other);
  }
  return (*this);
}

/**
 *  Get the instance id.
 *
 *  @return  The instance id.
 */
std::string const& instance::get_instance_id() const throw() {
  return (_instance_id);
}

/**
 *  Get the instance status.
 *
 *  @return  The instance status.
 */
instance::instance_status instance::get_instance_status() const throw() {
  for (unsigned int i = 0;
       i < sizeof(instance_status_list) / sizeof(*instance_status_list);
       ++i)
  if (_state_name == instance_status_list[i])
    return ((instance::instance_status)(i));
  return (instance::unknown);
}

/**
 *  Get the public ip address.
 *
 *  @return  The public ip address.
 */
std::string const& instance::get_public_ip_address() const throw() {
  return (_public_ip_address);
}

/**
 *  Init the bindings.
 */
void instance::_init_bindings() {
  add_member("InstanceId", _instance_id);
  add_member("ImageId", _image_id);
  {
    json_serializable& s = create_and_add_generic_sub_object("State");
    s.add_member("Code", _state_code);
    s.add_member("Name", _state_name);
  }
  add_member("PrivateDnsName", _private_dns_name);
  add_member("PublicDnsName", _public_dns_name);
  add_member("StateTransitionReason", _state_transition_reason);
  add_member("KeyName", _key_name);
  add_member("AmiLaunchIndex", _ami_launch_index);
  add_member("ProductCodes", _product_codes);
  add_member("InstanceType", _instance_type);
  {
    json_serializable& s = create_and_add_generic_sub_object("Placement");
    s.add_member("AvailabilityZone", _placement_availability_zone);
    s.add_member("GroupName", _placement_group_name);
    s.add_member("Tenancy", _placement_tenancy);
  }
  add_member("KernelId", _kernel_id);
  add_member("RamdiskId", _ramdisk_id);
  add_member("Platform", _platform);
  {
    json_serializable& s = create_and_add_generic_sub_object("Monitoring");
    s.add_member("State", _monitoring_state);
  }
  add_member("SubnetId", _subnet_id);
  add_member("VpcId", _vpc_id);
  add_member("PrivateIpAddress", _private_ip_address);
  add_member("PublicIpAddress", _public_ip_address);
  {
    json_serializable& s = create_and_add_generic_sub_object("StateReason");
    s.add_member("Code", _state_reason_code);
    s.add_member("Message", _state_reason_message);
  }
  add_member("Architecture", _architecture);
  add_member("RootDeviceType", _root_device_type);
  add_member("RootDeviceName", _root_device_name);
  add_member("BlockDeviceMappings", _block_device_mappings);
  add_member("VirtualizationType", _virtualization_type);
  add_member("InstanceLifecycle", _instance_lifecycle);
  add_member("SpotInstanceRequestId", _spot_instance_request_id);
  add_member("ClientToken", _client_token);
  add_ignored_member("Tags");
  add_member("SecurityGroups", _security_groups);
  add_member("SourceDestCheck", _source_dest_check);
  add_member("Hypervisor", _hypervisor);
  add_ignored_member("NetworkInterfaces");
  {
    json_serializable& s = create_and_add_generic_sub_object("IamInstanceProfile");
    s.add_member("Arn", _iam_instance_profile_arn);
    s.add_member("Id", _iam_instance_profile_id);
  }
  add_member("EbsOptimized", _ebs_optimized);
  add_member("LaunchTime", _launch_time);
  add_member("SriovNetSupport", _sriov_net_support);
}

/**
 *  Copy an object.
 *
 *  @param[in] other  Object to copy.
 */
void instance::_internal_copy(instance const& other) {
  _instance_id = other._instance_id;
  _image_id = other._image_id;
  _state_code = other._state_code;
  _state_name = other._state_name;
  _private_dns_name = other._private_dns_name;
  _public_dns_name = other._public_dns_name;
  _state_transition_reason = other._state_transition_reason;
  _key_name = other._key_name;
  _ami_launch_index = other._ami_launch_index;
  _product_codes = other._product_codes;
  _instance_type = other._instance_type;
  _placement_availability_zone = other._placement_availability_zone;
  _placement_group_name = other._placement_group_name;
  _placement_tenancy = other._placement_tenancy;
  _kernel_id = other._kernel_id;
  _ramdisk_id = other._ramdisk_id;
  _platform = other._platform;
  _monitoring_state = other._monitoring_state;
  _subnet_id = other._subnet_id;
  _vpc_id = other._vpc_id;
  _private_ip_address = other._private_ip_address;
  _public_ip_address = other._public_ip_address;
  _state_reason_code = other._state_reason_code;
  _state_reason_message = other._state_reason_message;
  _architecture = other._architecture;
  _root_device_type = other._root_device_type;
  _root_device_name = other._root_device_name;
  _block_device_mappings = other._block_device_mappings;
  _virtualization_type = other._virtualization_type;
  _instance_lifecycle = other._instance_lifecycle;
  _spot_instance_request_id = other._spot_instance_request_id;
  _client_token = other._client_token;
  _security_groups = other._security_groups;
  _source_dest_check = other._source_dest_check;
  _hypervisor = other._hypervisor;
  _iam_instance_profile_arn = other._iam_instance_profile_arn;
  _iam_instance_profile_id = other._iam_instance_profile_id;
  _iam_instance_id = other._iam_instance_id;
  _ebs_optimized = other._ebs_optimized;
  _sriov_net_support = other._sriov_net_support;
  _launch_time = other._launch_time;
}
