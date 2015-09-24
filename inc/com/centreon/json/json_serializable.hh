/*
** Copyright 2015 Centreon
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

#ifndef CC_JSON_JSON_SERIALIZABLE_HH
#  define CC_JSON_JSON_SERIALIZABLE_HH

#  include <map>
#  include <string>
#  include "com/centreon/json/jsmn.h"
#  include "com/centreon/json/json_iterator.hh"
#  include "com/centreon/json/json_writer.hh"
#  include "com/centreon/json/json_serializable_member.hh"
#  include "com/centreon/namespace.hh"
#  include "com/centreon/exceptions/basic.hh"

CC_BEGIN()

namespace json {
  /**
   *  @class json_serializable json_serializable.hh "com/centreon/json/json_serializable.hh"
   *  @brief Inherit from this if you want to make your class serializable.
   *
   *  Just add your members using add_member.
   */
  class                    json_serializable {
  public:
                           json_serializable();
                           json_serializable(json_serializable const& other);
    virtual                ~json_serializable();
    json_serializable&     operator=(json_serializable const& other);

    /**
     *  Add a member that needs to be serialized.
     */
    template <typename U>
    void                   add_member(
                             std::string const& serialized_name,
                             U& member,
                             int flags = 0) {
      _members[serialized_name] = new json_serializable_member_impl<U>(
                                        member, flags);
    }
    json_serializable&     create_and_add_generic_sub_object(
                             std::string const& sub_object,
                             int flags = 0);
    void                   add_ignored_member(
                             std::string const& serialized_name);

    virtual void           serialize(json_writer& writer) const;
    virtual void           unserialize(json_iterator it);
    virtual bool           is_null() const;

  private:
    // This is horribly ineficient. Ideally, something like Boost's
    // way of doing serialization should be implemented.
    std::map<std::string, json_serializable_member*>
                            _members;
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_SERIALIZABLE_HH
