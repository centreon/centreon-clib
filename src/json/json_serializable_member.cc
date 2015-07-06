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
#include "com/centreon/json/json_serializable_member.hh"

// Serialization specializations.

template <>
void com::centreon::json::serialize<std::string>(
       std::string const& member,
       json_writer &writer) {
  writer.add_string(member);
}

template <>
void com::centreon::json::serialize<int>(
       int const& member,
       json_writer &writer) {
  writer.add_number(member);
}

template <>
void com::centreon::json::serialize<unsigned int>(
       unsigned int const& member,
       json_writer &writer) {
  writer.add_number(member);
}

template <>
void com::centreon::json::serialize<bool>(
       bool const& member,
       json_writer &writer) {
  writer.add_boolean(member);
}

template <>
void com::centreon::json::serialize<double>(
       double const& member,
       json_writer &writer) {
  writer.add_double(member);
}

template <>
void com::centreon::json::serialize<com::centreon::timestamp>(
       timestamp const& member,
       json_writer &writer) {
  writer.add_string(member.to_utc());
}

// Deserialization specializations.

template <>
void com::centreon::json::unserialize<int>(
       int& member,
      json_iterator& it) {
  if (it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a number, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<unsigned int>(
       unsigned int& member,
      json_iterator& it) {
  if (it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a number, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<bool>(
       bool& member,
      json_iterator& it) {
  if (it.get_type() != json_iterator::boolean)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a boolean, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<char>(
       char& member,
      json_iterator& it) {
  if (it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a number, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<com::centreon::timestamp>(
      timestamp &member,
      json_iterator &it) {
  member = timestamp::from_utc(it.get_string());
}

template <>
void com::centreon::json::unserialize<std::string>(
      std::string& member,
      json_iterator &it) {
  if (it.get_type() != json_iterator::string)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a string, got " << it.get_string_type());
  member = it.get_string();
}

template <>
void com::centreon::json::unserialize<double>(
       double& member,
       json_iterator &it) {
  if (it.get_type() != json_iterator::string
      || it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a string or a number, got "
           << it.get_string_type());
  stream_unserialize(member, it);
}

// Serialization checks specializations.

template <>
bool com::centreon::json::should_be_serialized(
       bool const& member,
       int flags) {
  return (true);
}

template <>
bool com::centreon::json::should_be_serialized(
       int const& member,
       int flags) {
  return ((flags & json_serializable_member::serialize_on_null)
            || member != 0);
}

template <>
bool com::centreon::json::should_be_serialized(
       unsigned int const& member,
       int flags) {
  return ((flags & json_serializable_member::serialize_on_null)
            || member != 0);
}

template <>
bool com::centreon::json::should_be_serialized(
       std::string const& member,
       int flags) {
  return ((flags & json_serializable_member::serialize_on_null)
            || !member.empty());
}

template <>
bool com::centreon::json::should_be_serialized(
       double const& member,
       int flags) {
  return ((flags & json_serializable_member::serialize_on_null)
            || member != 0);
}

template <>
bool com::centreon::json::should_be_serialized(
       com::centreon::timestamp const& member, int flags) {
  return ((flags & json_serializable_member::serialize_on_null)
            || !member.is_null());
}
