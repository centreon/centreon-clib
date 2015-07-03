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
    json_serializable&     operator=(json_serializable const& other);
                           ~json_serializable();

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
    virtual void           unserialize(json_iterator& it);
    virtual bool           is_null() const;

  private:
    std::map<std::string, json_serializable_member*>
                            _members;
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_SERIALIZABLE_HH
