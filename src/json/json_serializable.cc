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
}

/**
 *  Add a member that needs to be serialized.
 */
template <typename V>
void json_serializable::add_member(
                         std::string const& serialized_name,
                         V& member) {
  _members[serialized_name] = new json_serializable_member_impl<V>(member);
}

/**
 *  Serialize everything.
 *
 *  @param[in] writer  The writer.
 */
void json_serializable::serialize(json_writer& writer) {
  for (std::map<std::string, json_serializable_member*>::const_iterator
         it = _members.begin(),
         end = _members.end();
       it != end;
       ++it) {
    writer.add_key(it->first);
    it->second->serialize(writer);
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
