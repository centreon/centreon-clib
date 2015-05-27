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
#include "com/centreon/json/json_iterator.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::json;

/**
 *  Constructor.
 *
 *  @param[in] js            The json string.
 *  @param[in] tokens        Parsed tokens.
 *  @param[in] token_number  Number of parsed tokens.
 */
json_iterator::json_iterator(
                 const char* js,
                 jsmntok_t* tokens,
                 size_t token_number)
  : _js(js),
    _tokens(tokens),
    _token_number(token_number),
    _index(0) {}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
json_iterator::json_iterator(json_iterator const& other)
  : _js(other._js),
    _tokens(other._tokens),
    _token_number(other._token_number),
    _index(other._index) {}

/**
 *  Assignment operator.
 *
 *  @return
 */
json_iterator& json_iterator::operator=(json_iterator const& other) {
  if (this != &other) {
    _js = other._js;
    _tokens = other._tokens;
    _token_number = other._token_number;
    _index = other._index;
  }
}

/**
 *  Destructor.
 */
json_iterator::~json_iterator() {}

/**
 *  Go forward a node. Do not enter child nodes.
 *
 *  @return  A reference to this iterator.
 */
json_iterator& json_iterator::operator++() {
  _index = _tokens[_index].size + 1;
  return (*this);
}

/**
 *  Get the type of this node.
 *
 *  @return The type of this node.
 */
json_iterator::type json_iterator::get_type() const {
  switch (_tokens[_index].type) {
    case JSMN_OBJECT:
      return (object);
    case JSMN_ARRAY:
      return (array);
    case JSMN_STRING:
      return (string);
    case JSMN_PRIMITIVE:
      switch (_js[_tokens[_index].start]) {
        case 't':
        case 'f':
          return (boolean);
        case 'n':
          return (null);
        default:
          return (number);
      }
  }
}

/**
 *  Get this node as a string.
 *
 *  @return  This node as a string.
 */
std::string json_iterator::get_string() const {
  return (std::string(
            _js[_tokens[_index].start],
             _tokens[_index].end - _tokens[_index].start));
}

/**
 *  Get this node as an integer.
 *
 *  @return  This node as an integer.
 */
int json_iterator::get_integer() const {
  std::stringstream ss;
  ss << get_string();
  int ret;
  ss >> ret;
  if (ss.fail())
    throw (exceptions::basic()
           << "couldn't parse '"
           << get_string() << "' into an integer");
  return (ret);
}

/**
 *  Get this node as a boolean.
 *
 *  @return  The value of this boolean.
 */
bool json_iterator::get_bool() const {
  std::string str = get_string();
  return (str == "true" ? true : false);
}

/**
 *  Is this node null?
 *
 *  @return  True if this node is null.
 */
bool json_iterator::is_null() const {
  return (get_type() == null);
}

/**
 *  Get the number of children of this node.
 *
 *  @return  Number of children of this node.
 */
int json_iterator::children() const {
  return (_tokens[_index].size);
}

/**
 *  Go in the children, if any.
 *
 *  @return  A json_iterator on the first children, if any.
 */
json_iterator json_iterator::enter_children() const {
  if (_tokens[_index].size > 0)
    return (json_iterator(_js, _tokens + _index + 1, _tokens[_index].size));
  else
    return (json_iterator(_js, _tokens, 0));
}

/**
 *  Did this iterator end?
 *
 *  @return  True if this iterator is at the end.
 */
bool json_iterator::end() const {
  return (_index >= _token_number);
}
