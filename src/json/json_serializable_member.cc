/*
** Copyright 2011-2015 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
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
      json_iterator const& it) {
  if (it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a number, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<unsigned int>(
       unsigned int& member,
      json_iterator const& it) {
  if (it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a number, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<bool>(
       bool& member,
      json_iterator const& it) {
  if (it.get_type() != json_iterator::boolean)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a boolean, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<char>(
       char& member,
      json_iterator const& it) {
  if (it.get_type() != json_iterator::number)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a number, got " << it.get_string_type());
  stream_unserialize(member, it);
}

template <>
void com::centreon::json::unserialize<com::centreon::timestamp>(
      timestamp &member,
      json_iterator const& it) {
  member = timestamp::from_utc(it.get_string());
}

template <>
void com::centreon::json::unserialize<std::string>(
      std::string& member,
      json_iterator const& it) {
  if (it.get_type() != json_iterator::string)
    throw (exceptions::basic()
           << "json: cannot unserialize '" << it.get_string()
           << "', expected a string, got " << it.get_string_type());
  member = it.get_string();
}

template <>
void com::centreon::json::unserialize<double>(
       double& member,
       json_iterator const& it) {
  if (it.get_type() != json_iterator::string
      && it.get_type() != json_iterator::number)
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
  (void) member;
  (void) flags;
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
