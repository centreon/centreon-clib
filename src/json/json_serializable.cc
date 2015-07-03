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

#include <memory>
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
 *  @param[in] other  Object to copy.
 */
json_serializable::json_serializable(json_serializable const& other) {
  _members = other._members;
}

/**
 *  Assignment operator.
 *
 *  @param[in]  other  Object to copy.
 *
 *  @return  Reference to this.
 */
json_serializable& json_serializable::operator=(json_serializable const& other) {
  if (this != &other) {
    _members = other._members;
  }
  return (*this);
}

/**
 *  Destructor.
 */
json_serializable::~json_serializable() {
  for (std::map<std::string, json_serializable_member*>::iterator
         it = _members.begin(),
         end = _members.end();
       it != end;
       ++it)
    delete it->second;
}

/**
 *  Create a generic sub object.
 *
 *  @param[in] sub_object  The name of the generic sub object.
 */
json_serializable& json_serializable::create_and_add_generic_sub_object(
                     std::string const& sub_object,
                     int flags) {
  std::auto_ptr<json_serializable> object(new json_serializable);
  add_member(
    sub_object,
    *object.get(),
    flags | json_serializable_member::own_reference);
  return (*object.release());
}

/**
 *  Add an ignored member.
 *
 *  @param[in] serialized_name  The name of the ignored member.
 */
void json_serializable::add_ignored_member(
                          std::string const& serialized_name) {
  create_and_add_generic_sub_object(serialized_name);
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
