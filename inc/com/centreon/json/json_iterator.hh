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

#  include <vector>
#  include <string>
#  include "com/centreon/json/jsmn.h"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace json {
  /**
   *  @class json_iterator json_iterator.hh "com/centreon/json/json_iterator.hh"
   *  @brief Iterate over the tokens of a json document.
   *
   *  As an example, the document:
   *  '{ "name" : "Jack", "age" : 27 }'
   *
   *  contains 5 tokens: the toplevel object, with 4 children:
   *  name, Jack, age and 27. Pair association needs to be done
   *  manually, but is simple: for the direct children of an object,
   *  one token of two is a key, the other a value.
   */
  class                    json_iterator {
  public:
                           json_iterator(
                             const char* js,
                             const jsmntok_t* tokens,
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
    type                   get_type() const throw();
    std::string            get_string_type() const;
    std::string            get_string() const;
    int                    get_integer() const;
    bool                   get_bool() const;
    bool                   is_null() const throw();

    int                    children() const throw();
    json_iterator          enter_children() const throw();

    bool                   end() const throw();

  private:
    const char*            _js;
    const jsmntok_t*        _tokens;
    size_t                 _token_number;
    size_t                 _index;

                           json_iterator();
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_ITERATOR_HH
