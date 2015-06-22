/*
** Copyright 2011-2015 Merethis
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
#include "com/centreon/json/json_serializable.hh"
#include "com/centreon/json/json_serializable_member.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::json;

/**
 *  Default constructor.
 */
json_serializable::json_serializable() {}

/**
 *  Copy constructor.
 *
 *  @param[in] other  The object to copy.
 */
json_serializable::json_serializable(json_serializable const& other)
  : _members(other._members) {}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return  Reference to this.
 */
json_serializable& json_serializable::operator=(json_serializable const& other) {
  if (this != &other)
    _members = other._members;
  return (*this);
}

/**
 *  Destructor.
 */
json_serializable::~json_serializable() {
  for (std::map<std::string, json_serializable_member*>::const_iterator
         it = _members.begin(),
         end  = _members.end();
       it != end;
       ++it)
  delete it->second;
  for (std::vector<json_serializable*>::const_iterator
         it = _generic_sub_objects.begin(),
         end  = _generic_sub_objects.end();
       it != end;
       ++it)
  delete *it;
}

/**
 *  Create a generic sub object.
 *
 *  @param[in] sub_object  The name of the generic sub object.
 */
json_serializable& json_serializable::create_and_add_generic_sub_object(
                     std::string const& sub_object,
                     int flags) {
  _generic_sub_objects.push_back(new json_serializable);
  add_member(sub_object, *_generic_sub_objects.back(), flags);
  return (*_generic_sub_objects.back());
}

/**
 *  Serialize everything.
 *
 *  @param[in] writer  The writer.
 */
void json_serializable::serialize(json_writer& writer) const {
  for (std::map<std::string, json_serializable_member*>::const_iterator
         it = _members.begin(),
         end = _members.end();
       it != end;
       ++it) {
    if (it->second->should_be_serialized()) {
      writer.add_key(it->first);
      it->second->serialize(writer);
    }
  }
}

/**
 *  Unserialize everything.
 *
 *  @param[in] it  The iterator.
 */
void json_serializable::unserialize(json_iterator& it) {
  std::map<std::string, json_serializable_member*>::const_iterator
    found = _members.find(it.get_string());
  if (found == _members.end())
    throw (exceptions::basic()
           << "can't find the member '"
           << it.get_string() << "' in serialization");
  ++it;
  found->second->unserialize(it);
}

/**
 *  @brief Is this json object null?
 *
 *  The meaning of a null json object is object dependent.
 *  A null json object won't be serialized by default.
 *
 *  @return  True if this is a null json object.
 */
bool json_serializable::is_null() const {
  for (std::map<std::string, json_serializable_member*>::const_iterator
         it = _members.begin(),
         end = _members.end();
       it != end;
       ++it)
    if (it->second->should_be_serialized())
      return (false);
  return (true);
}
