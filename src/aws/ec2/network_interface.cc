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

#include "com/centreon/process.hh"
#include "com/centreon/aws/ec2/network_interface.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
network_interface::private_ip_address::private_ip_address()
  : primary(false) {
  _init_bindings();
}
/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
network_interface::private_ip_address::private_ip_address(
  network_interface::private_ip_address const& other)
  : json::json_serializable(other),
    private_ip_address_value(other.private_ip_address_value),
    primary(other.primary) {
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this object.
 */
network_interface::private_ip_address&
  network_interface::private_ip_address::operator=(
    network_interface::private_ip_address const& other) {
  if (this != &other) {
    private_ip_address_value = other.private_ip_address_value;
    primary = other.primary;
  }
  return (*this);
}

/**
 *  Init the bindings.
 */
void network_interface::private_ip_address::_init_bindings() {
  add_member("PrivateIpAddress", private_ip_address_value);
  add_member("Primary", primary);;
}

/**
 *  Default constructor.
 */
network_interface::network_interface()
  : _device_index(0),
    _delete_on_termination(false),
    _associate_ip_address(true) {
  _init_bindings();
}
/**
 *  Copy constructor.
 *
 *  @param[in] other  Object to copy.
 */
network_interface::network_interface(
  network_interface const& other)
  : json::json_serializable(other){
  _internal_copy(other);
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  Object to copy.
 *
 *  @return           Reference to this object.
 */
network_interface& network_interface::operator=(
                     network_interface const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Destructor.
 */
network_interface::~network_interface() {

}

/**
 *  Init the bindings.
 */
void network_interface::_init_bindings() {
  add_member("NetworkInterfaceId", _network_interface_id);
  add_member("DeviceIndex", _device_index);
  add_member("SubnetId", _subnet_id);
  add_member("Description", _description);
  add_member("PrivateIpAddress", _private_ip_address);
  add_member("Groups", _groups);
  add_member("DeleteOnTermination", _delete_on_termination);
  add_member("PrivateIpAddresses", _private_ip_addresses);
  add_member("SecondaryPrivateIpAddressCount", _secondary_private_ip_address_count);
  add_member("AssociateIpAddress", _associate_ip_address);
}

/**
 *  Copy an object.
 *
 *  @param other  Object to copy.
 */
void network_interface::_internal_copy(network_interface const& other) {
  _network_interface_id = other._network_interface_id;
  _device_index = other._device_index;
  _subnet_id = other._subnet_id;
  _description = other._description;
  _private_ip_address = other._private_ip_address;
  _groups = other._groups;
  _delete_on_termination = other._delete_on_termination;
  _private_ip_addresses = other._private_ip_addresses;
  _secondary_private_ip_address_count = other._secondary_private_ip_address_count;
  _associate_ip_address = other._associate_ip_address;
}
