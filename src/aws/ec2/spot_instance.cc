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

#include "com/centreon/aws/ec2/spot_instance.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
spot_instance::spot_instance()
  : _spot_price(0) {
  _init_bindings();
}

/**
 *  Destructor.
 */
spot_instance::~spot_instance() {

}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
spot_instance::spot_instance(spot_instance const& other) {
  _internal_copy(other);
  _init_bindings();
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           A reference to this object.
 */
spot_instance& spot_instance::operator=(spot_instance const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Init the bindings.
 */
void spot_instance::_init_bindings() {
  add_member("Fault", _fault);
  add_member("Status", _status);
  add_member("LaunchSpecification", _launch_specification);
  add_member("ValidFrom", _valid_from);
  add_member("ValidUntil", _valid_until);
  add_member("LaunchGroup", _launch_group);
  add_member("AvailabilityZoneGroup", _availability_zone_group);
  add_member("ProductDescription", _product_description);
  add_member("InstanceId", _instance_id);
  add_member("SpotInstanceRequestId", _spot_instance_request_id);
  add_member("State", _state);
  add_member("LaunchedAvailabilityZone", _launched_availability_zone);
  add_member("Type", _type);
  add_member("CreateTime", _create_time);
  add_member("SpotPrice", _spot_price);
}

/**
 *  Copy an object.
 *
 *  @param[in] other  The object to copy.
 */
void spot_instance::_internal_copy(spot_instance const& other) {
  _fault = other._fault;
  _status = other._status;
  _launch_specification = other._launch_specification;
  _valid_from = other._valid_from;
  _valid_until = other._valid_until;
  _launch_group = other._launch_group;
  _availability_zone_group = other._availability_zone_group;
  _product_description = other._product_description;
  _instance_id = other._instance_id;
  _spot_instance_request_id = other._spot_instance_request_id;
  _state = other._state;
  _launched_availability_zone = other._launched_availability_zone;
  _type = other._type;
  _create_time = other._create_time;
  _spot_price = other._spot_price;
}
