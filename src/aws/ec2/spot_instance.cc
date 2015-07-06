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

#include <cstring>
#include "com/centreon/aws/ec2/spot_instance.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon;
using namespace com::centreon::aws::ec2;

static const char* instance_string[] =
  {"open", "failed", "active", "canceled", "closed", "unknown"};

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

spot_instance_fault const& spot_instance::get_fault() const throw() {
  return (_fault);
}

spot_instance_status const& spot_instance::get_status() const throw() {
  return (_status);
}

launch_specification const& spot_instance::get_launch_specification() const throw() {
  return (_launch_specification);
}

timestamp spot_instance::get_valid_from() const throw() {
  return (_valid_from);
}

timestamp spot_instance::get_valid_until() const throw() {
  return (_valid_until);
}

std::string const& spot_instance::get_launch_group() const throw() {
  return (_launch_group);
}

std::string const& spot_instance::get_availability_zone_group() const throw() {
  return (_availability_zone_group);
}

std::string const& spot_instance::get_product_description() const throw() {
  return (_product_description);
}

std::string const& spot_instance::get_instance_id() const throw() {
  return (_instance_id);
}

std::string const& spot_instance::get_spot_instance_request_id() const throw() {
  return (_spot_instance_request_id);
}

/**
 *  Is this instance running?
 *
 *  @return  True if this instance is running.
 */
bool spot_instance::is_running() const throw() {
  spot_instance::spot_instance_state state = get_state();
  return (state == open || state == active);
}

spot_instance::spot_instance_state spot_instance::get_state() const throw() {
  get_state_from_string(get_state_string());
}

std::string const& spot_instance::get_state_string() const throw() {
  return (_state);
}

spot_instance::spot_instance_state
  spot_instance::get_state_from_string(std::string const& str) throw() {
  for (size_t i = 0;
       i < sizeof(instance_string) / sizeof(*instance_string);
       ++i)
    if (str == instance_string[i])
      return ((spot_instance_state)(i));
  return (unknown);
}

std::string const& spot_instance::get_launched_availability_zone() const throw() {
  return (_launched_availability_zone);
}

std::string const& spot_instance::get_type() const throw() {
  return (_type);
}

timestamp spot_instance::get_create_time() const throw()  {
  return (_create_time);
}

double spot_instance::get_spot_price() const throw() {
  return (_spot_price);
}

void spot_instance::set_fault(spot_instance_fault const& fault) {
  _fault = fault;
}

void spot_instance::set_status(spot_instance_status const& status) {
  _status = status;
}

void spot_instance::set_launch_specification(launch_specification const& val) {
  _launch_specification = val;
}

void spot_instance::set_valid_from(timestamp valid_from) {
  _valid_from = valid_from;
}

void spot_instance::set_valid_until(timestamp valid_until) {
  _valid_until = valid_until;
}

void spot_instance::set_launch_group(std::string const& launch_group) {
  _launch_group = launch_group;
}

void spot_instance::set_availability_zone_groupe(std::string const& val) {
  _availability_zone_group = val;
}

void spot_instance::set_product_description(std::string const& val) {
  _product_description = val;
}

void spot_instance::set_instance_id(std::string const& instance_id) {
  _instance_id = instance_id;
}

void spot_instance::set_spot_instance_request_id(std::string const& val) {
  _spot_instance_request_id = val;
}

void spot_instance::set_state(std::string const& state) {
  _state = state;
}

void spot_instance::set_state(spot_instance_state const& state) {
  if (state == unknown)
    _state = "";
  else
    _state = instance_string[state];
}

void spot_instance::set_launched_availability_zone(std::string const& val) {
  _launched_availability_zone = val;
}

void spot_instance::set_type(std::string const& type) {
  _type = type;
}

void spot_instance::set_create_time(timestamp create_time) {
  _create_time = create_time;
}

void spot_instance::set_spot_price(double spot_price) {
  _spot_price = spot_price;
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
