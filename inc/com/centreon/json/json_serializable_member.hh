/*
** Copyright 2011-2013 Merethis
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

#ifndef CC_JSON_JSON_SERIALIZABLE_MEMBER_HH
#  define CC_JSON_JSON_SERIALIZABLE_MEMBER_HH

#  include <map>
#  include <string>
#  include <sstream>
#  include "com/centreon/json/jsmn.h"
#  include "com/centreon/json/json_iterator.hh"
#  include "com/centreon/json/json_writer.hh"
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/exceptions/basic.hh"
#  include "com/centreon/timestamp.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace json {
  /**
   *  @class json_serializable_member json_serializable_member.hh "com/centreon/json/json_serializable_member.hh"
   *  @brief Represents a serializable member.
   */
  class                    json_serializable_member {
  public:
    virtual                ~json_serializable_member();

    virtual void           serialize(json_writer& writer) const = 0;
    virtual void           unserialize(json_iterator const& iterator) const = 0;
  };

  template <typename T>
  void serialize(T& member, json_writer& writer) {
    writer.add_null();
  }

  template <>
  void serialize<std::string>(std::string& member, json_writer &writer) {
    writer.add_string(member);
  }

  template <>
  void serialize<int>(int& member, json_writer &writer) {
    writer.add_number(member);
  }

  template <>
  void serialize<unsigned int>(unsigned int& member, json_writer &writer) {
    writer.add_number(member);
  }

  template <>
  void serialize<bool>(bool& member, json_writer &writer) {
    writer.add_boolean(member);
  }

  template <>
  void serialize<timestamp>(timestamp& _member, json_writer &writer) {
    // TODO:
    //writer.add_string();
  }

  template <typename T>
  void unserialize(T& member, json_iterator& it) {
    std::stringstream ss;

    ss << it.get_string();
    ss >> member;
  }

  template <>
  void unserialize<json::json_serializable>(json_serializable& member, json_iterator& it) {
    json_iterator children_iterator = it.enter_children();
    member.unserialize(children_iterator);
  }

  template <typename T>
  class                    json_serializable_member_impl :json_serializable_member {
  public:
                           json_serializable_member_impl(T& t)
                            : _member(&t) {}
                           json_serializable_member_impl(
                             json_serializable_member_impl const& other)
                            : _member(other._member) {}
    json_serializable_member_impl
                           operator=(json_serializable_member_impl const& other) {
      if (this != &other)
        _member = other._member;
      return (*this);
    }

                           ~json_serializable_member_impl() {}

    /**
     *  Serialize the member.
     *
     *  @param[in] writer  The json writer.
     */
    void                   serialize(json_writer& writer) const {
      json::serialize(*_member, writer);
    }

    /**
     *  Unserialize the member.
     *
     *  @param[in] iterator  The json iterator.
     */
    void                   unserialize(json_iterator& iterator) const {
      json::unserialize(*_member, iterator);
    }

  private:
    T* _member;
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_SERIALIZABLE_MEMBER_HH
