/*
** Copyright 2015 Centreon
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
#include "com/centreon/aws/ec2/block_device_mapping.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
block_device_mapping::ebs::ebs()
  : lops(0),
    encrypted(false) {
  _init_bindings();
}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
block_device_mapping::ebs::ebs(block_device_mapping::ebs const& other)
  : json::json_serializable(other) {
  _internal_copy(other);
  _init_bindings();
}

/**
 *  Destructor.
 */
block_device_mapping::ebs::~ebs() {}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this.
 */
block_device_mapping::ebs& block_device_mapping::ebs::operator=(
  block_device_mapping::ebs const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  @brief Is this object null?
 *
 *  Null objects won't be serialized.
 *
 *  @return  True if this object is null.
 */
bool block_device_mapping::ebs::is_null() const {
  return (snapshot_id.empty()
            && volume_size.empty()
            && delete_on_termination
            && volume_type.empty()
            && volume_id.empty()
            && attach_time.is_null()
            && lops == 0
            && encrypted == false);
}

/**
 *  Init the bindings.
 */
void block_device_mapping::ebs::_init_bindings() {
  add_member("AttachTime", attach_time);
  add_member("Status", status);
  add_member("SnapshotId", snapshot_id);
  add_member("VolumeSize", volume_size);
  add_member("DeleteOnTermination", delete_on_termination);
  add_member("VolumeType", volume_type);
  add_member("VolumeId", volume_id);
  add_member("Lops", lops);
  add_member("Encrypter", encrypted);
}

/**
 *  Copy an object.
 *
 *  @param[in] other  The object to copy.
 */
void block_device_mapping::ebs::_internal_copy(ebs const& other) {
  snapshot_id = other.snapshot_id;
  volume_size = other.volume_size;
  delete_on_termination = other.delete_on_termination;
  volume_type = other.volume_type;
  lops = other.lops;
  encrypted = other.encrypted;
}

/**
 *  Default constructor.
 */
block_device_mapping::block_device_mapping() {
  _init_bindings();
}
/**
 *  Copy constructor.
 *
 *  @param[in] other  Object to copy.
 */
block_device_mapping::block_device_mapping(
  block_device_mapping const& other)
  : json::json_serializable(other) {
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
block_device_mapping& block_device_mapping::operator=(
                        block_device_mapping const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Destructor.
 */
block_device_mapping::~block_device_mapping() {

}

/**
 *  Init the bindings.
 */
void block_device_mapping::_init_bindings() {
  add_member("VirtualName", _virtual_name);
  add_member("DeviceName", _device_name);
  add_member("Ebs", _ebs);
  add_member("NoDevice", _no_device);
}

/**
 *  Copy an object.
 *
 *  @param other  Object to copy.
 */
void block_device_mapping::_internal_copy(block_device_mapping const& other) {
  _virtual_name = other._virtual_name;
  _device_name = other._device_name;
  _ebs = other._ebs;
  _no_device = other._no_device;
}
