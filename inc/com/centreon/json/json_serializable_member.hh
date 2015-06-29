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
    virtual                ~json_serializable_member() {}

    enum                   serializable_flags {
                           none = 0,
                           serialize_on_null = 1
    };

    virtual void           serialize(json_writer& writer) const = 0;
    virtual void           unserialize(json_iterator& iterator) const = 0;
    virtual bool           should_be_serialized() const  = 0;
  };

  template <typename T>
  void serialize(std::vector<T> const& member, json_writer& writer) {
    writer.open_array();
    for (typename std::vector<T>::const_iterator
           it = member.begin(),
           end = member.end();
         it != end;
         ++it)
      serialize(*it, writer);
    writer.close_array();
  }

  template <typename T>
  void serialize(T const& member, json_writer& writer) {
    writer.open_object();
    member.serialize(writer);
    writer.close_object();
  }

  template <>
  void serialize<std::string>(std::string const& member, json_writer &writer);
  template <>
  void serialize<int>(int const& member, json_writer &writer);
  template <>
  void serialize<unsigned int>(unsigned int const& member, json_writer &writer);
  template <>
  void serialize<bool>(bool const& member, json_writer &writer);
  template <>
  void serialize<double>(double const& member, json_writer &writer);
  template <>
  void serialize<timestamp>(timestamp const& _member, json_writer &writer);

  template <typename T>
  void  stream_unserialize(T& member, json_iterator& it) {
    std::stringstream ss;

    ss << it.get_string();
    ss >> member;
  }

  template <typename T>
  void unserialize(std::vector<T>& member, json_iterator& it) {
    if (it.get_type() != json_iterator::array)
      throw (exceptions::basic()
             << "json: cannot unserialize '" << it.get_string()
             << "', expected an array, got " << it.get_string_type());
    json_iterator children = it.enter_children();
    for (; !children.is_null(); ++children) {
      member.push_back(T());
      unserialize(member.back(), children);
    }
  }

  template <typename T>
  void unserialize(T& member, json_iterator& it) {
    if (it.get_type() != json_iterator::object)
      throw (exceptions::basic()
             << "json: cannot unserialize '" << it.get_string()
             << "', expected an object, got " << it.get_string_type());
    json_iterator children_iterator = it.enter_children();
    member.unserialize(children_iterator);
  }

  template <>
  void unserialize<int>(
         int& member,
        json_iterator& it);
  template <>
  void unserialize<unsigned int>(
         unsigned int& member,
        json_iterator& it);
  template <>
  void unserialize<bool>(
         bool& member,
        json_iterator& it);
  template <>
  void unserialize<char>(
         char& member,
        json_iterator& it);
  template <>
  void unserialize<timestamp>(
        timestamp &member,
        json_iterator &it);
  template <>
  void unserialize<std::string>(
        std::string& member,
        json_iterator &it);
  template <>
  void unserialize<double>(
         double& member,
         json_iterator &it);

  template <typename T>
  bool should_be_serialized(std::vector<T> const& member, int _flags) {
    return ((_flags & json_serializable_member::serialize_on_null)
              || !member.empty());
  }

  template <typename T>
  bool should_be_serialized(T const& member, int _flags) {
    return ((_flags & json_serializable_member::serialize_on_null)
              || !member.is_null());
  }

  template <>
  bool should_be_serialized(bool const& member, int flags);
  template <>
  bool should_be_serialized(int const& member, int flags);
  template <>
  bool should_be_serialized(unsigned int const& member, int flags);
  template <>
  bool should_be_serialized(std::string const& member, int flags);
  template <>
  bool should_be_serialized(double const& member, int flags);

  template <typename T>
  class                    json_serializable_member_impl :
                             public json_serializable_member {
  public:
                           json_serializable_member_impl(T& t, int flags)
                            : _member(&t), _flags(flags) {}
                           json_serializable_member_impl(
                             json_serializable_member_impl const& other)
                            : _member(other._member), _flags(other._flags) {}
    json_serializable_member_impl&
                           operator=(
                             json_serializable_member_impl const& other) {
      if (this != &other) {
        _member = other._member;
        _flags = other._flags;
      }
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

    /**
     *  Should this member be serialized?
     *
     *  @return  True if this member should be serialized.
     */
    bool                   should_be_serialized() const {
      return (json::should_be_serialized(*_member, _flags));
    }

  private:
    T* _member;
    int _flags;
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_SERIALIZABLE_MEMBER_HH
