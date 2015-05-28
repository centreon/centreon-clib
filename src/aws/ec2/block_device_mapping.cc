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

#include "com/centreon/process.hh"
#include "com/centreon/aws/ec2/block_device_mapping.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
block_device_mapping::block_device_mapping()
  : _ebs_lops(0),
    _ebs_encrypted(false) {

}
/**
 *  Copy constructor.
 *
 *  @param[in] other  Object to copy.
 */
block_device_mapping::block_device_mapping(
  block_device_mapping const& other) {
  _internal_copy(other);
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
 *  Copy an object.
 *
 *  @param other  Object to copy.
 */
void block_device_mapping::_internal_copy(block_device_mapping const& other) {
  _virtual_name = other._virtual_name;
  _device_name = other._device_name;
  _ebs_snapshot_id = other._ebs_snapshot_id;
  _ebs_volume_size = other._ebs_volume_size;
  _ebs_delete_on_termination = other._ebs_delete_on_termination;
  _ebs_volume_type = other._ebs_volume_type;
  _ebs_lops = other._ebs_lops;
  _ebs_encrypted = other._ebs_encrypted;
  _no_device = other._no_device;
}
