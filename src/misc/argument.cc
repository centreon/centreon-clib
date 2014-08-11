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

#include <iostream>
#include "com/centreon/misc/argument.hh"

using namespace com::centreon::misc;

/**
 *  Default constructor.
 *
 *  @param[in] long_name    Argument's long name.
 *  @param[in] name         Argument's name.
 *  @param[in] description  Argument's description.
 *  @param[in] has_value    Argument need one or multiple values.
 */
argument::argument(
            std::string const& long_name,
            char name,
            std::string const& description,
            argument::value_number has_value)
  : _description(description),
    _has_value(has_value),
    _long_name(long_name),
    _name(name) {}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
argument::argument(argument const& other) {
  _internal_copy(other);
}

/**
 *  Destructor.
 */
argument::~argument() throw () {}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return This object.
 */
argument& argument::operator=(argument const& other) {
  return (_internal_copy(other));
}

/**
 *  Equal operator.
 *
 *  @param[in] other  The object to compare.
 *
 *  @return Tue if objects are equal, otherwise false.
 */
bool argument::operator==(argument const& other) const throw () {
  return (_name == other._name
          && _long_name == other._long_name
          && _values == other._values
          && _has_value == other._has_value
          && _description == other._description);
}

/**
 *  Not equal operator.
 *
 *  @param[in] other  The object to compare.
 *
 *  @return True if objects are different, otherwise false.
 */
bool argument::operator!=(argument const& other) const throw () {
  return (!operator==(other));
}

/**
 *  Add value to argument.
 *
 *  @param[in] value  New value.
 */
void argument::add_value(std::string const& value) {
  _values.push_back(value);
  return ;
}

/**
 *  Get the argument description.
 *
 *  @return The description.
 */
std::string const& argument::get_description() const throw () {
  return (_description);
}

/**
 *  Get if argument need to has value.
 *
 *  @return Number of arguments allowed.
 */
argument::value_number argument::get_has_value() const throw () {
  return (_has_value);
}

/**
 *  Get the long name of the argument.
 *
 *  @return The long name.
 */
std::string const& argument::get_long_name() const throw () {
  return (_long_name);
}

/**
 *  Get the name of the argument.
 *
 *  @return The name.
 */
char argument::get_name() const throw () {
  return (_name);
}

/**
 *  Get the values.
 *
 *  @return The values.
 */
std::list<std::string> const& argument::get_values() const throw () {
  return (_values);
}

/**
 *  Get if argument is set.
 *
 *  @return True if argument is set.
 */
bool argument::is_set() const throw () {
  return (!_values.empty());
}

/**
 *  Set the argument description.
 *
 *  @param[in] description  The description.
 */
void argument::set_description(std::string const& description) {
  _description = description;
}

/**
 *  Set is the argument need a value.
 *
 *  @param[in] val  Number of arguments allowed.
 */
void argument::set_has_value(argument::value_number val) throw () {
  _has_value = val;
}

/**
 *  Set the long name of the argument.
 *
 *  @param[in] long_name  The long name.
 */
void argument::set_long_name(std::string const& long_name) {
  _long_name = long_name;
}

/**
 *  Set the name of the argument.
 *
 *  @param[in] name  The name.
 */
void argument::set_name(char name) {
  _name = name;
}

/**
 *  Internal copy.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return This object.
 */
argument& argument::_internal_copy(argument const& other) {
  if (this != &other) {
    _description = other._description;
    _has_value = other._has_value;
    _long_name = other._long_name;
    _name = other._name;
    _values = other._values;
  }
  return (*this);
}
