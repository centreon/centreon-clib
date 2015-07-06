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

#include <sstream>
#include "com/centreon/json/json_writer.hh"

using namespace com::centreon::json;

/**
 *  Default constructor.
 */
json_writer::json_writer() {
}

/**
 *  Destructor.
 */
json_writer::~json_writer() {

}

/**
 *  Get the constructed string.
 *
 *  @return  The constructed string.
 */
std::string const& json_writer::get_string() const {
  return (_string);
}

/**
 *  Open a json object.
 */
void json_writer::open_object() {
  _put_comma();
  _string += '{';
}

/**
 *  Close a json object.
 */
void json_writer::close_object() {
  _string += '}';
}

/**
 *  Open a json array.
 */
void json_writer::open_array() {
  _put_comma();
  _string += '[';
}

/**
 *  Close a json array.
 */
void json_writer::close_array() {
  _string += ']';
}

/**
 *  Add a key.
 *
 *  @param[in] key  The key name.
 */
void json_writer::add_key(std::string const& key) {
  add_string(key);
  _string += ":";
}

/**
 *  Add a string.
 *
 *  @param[in] str  The string.
 */
void json_writer::add_string(std::string const& str) {
  _put_comma();
  ((_string += '"') += str) += '"';
}

/**
 *  Add a number.
 *
 *  @param[in] number  The number.
 */
void json_writer::add_number(long long number) {
  _put_comma();
  std::stringstream ss;
  ss << number;
  std::string res;
  ss >> res;
  _string += res;
}

/**
 *  Add a double.
 *
 *  @param[in] number  The number in double precision.
 */
void json_writer::add_double(double number) {
  _put_comma();
  std::stringstream ss;
  ss << number;
  std::string res;
  ss >> res;
  _string += res;
}

/**
 *  Add a null.
 */
void json_writer::add_null() {
  _put_comma();
  _string += "null";
}

/**
 *  Add a boolean.
 *
 *  @param[in] value  The value of the boolean.
 */
void json_writer::add_boolean(bool value) {
  _put_comma();
  if (value)
    _string += "true";
  else
    _string += "false";
}

/**
 *  Put a comma, if needed.
 */
void json_writer::_put_comma() {
  if (!_string.empty()
      && _string[_string.size() - 1] != ':'
      && _string[_string.size() -1] != '{'
      && _string[_string.size() -1] != '[')
    _string += ',';
}
