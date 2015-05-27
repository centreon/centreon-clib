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

#ifndef CC_JSON_JSON_ITERATOR_HH
#  define CC_JSON_JSON_ITERATOR_HH

#  define JSMN_PARENT_LINKS 1

#  include <vector>
#  include <string>
#  include "com/centreon/json/jsmn.h"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace json {
  /**
   *  @class json_iterator json_iterator.hh "com/centreon/json/json_iterator.hh"
   *  @brief Iterate over a json document.
   */
  class                    json_iterator {
  public:
                           json_iterator(
                             const char* js,
                             jsmntok_t* tokens,
                             size_t token_number);
                           json_iterator(json_iterator const&);
    json_iterator&         operator=(json_iterator const&);
                           ~json_iterator();
    json_iterator&         operator++();

    enum                   type {
                           object,
                           array,
                           string,
                           number,
                           boolean,
                           null
    };
    type                   get_type() const;
    std::string            get_string() const;
    int                    get_integer() const;
    bool                   get_bool() const;
    bool                   is_null() const;

    int                    children() const;
    json_iterator          enter_children() const;

    bool                   end() const;

  private:
    const char*            _js;
    jsmntok_t*             _tokens;
    size_t                 _token_number;
    size_t                 _index;

                           json_iterator();
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_ITERATOR_HH
