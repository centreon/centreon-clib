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

#ifndef CC_JSON_JSON_PARSER_HH
#  define CC_JSON_JSON_PARSER_HH

#  include <vector>
#  include <string>
#  include "com/centreon/json/jsmn.h"
#  include "com/centreon/json/json_iterator.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace json {
  /**
   *  @class json_parser json_parser.hh "com/centreon/json/json_parser.hh"
   *  @brief Simple json parser based on jsmn.
   */
  class                    json_parser {
  public:
                           json_parser();
                           ~json_parser();

    void                   parse(std::string const& js);
    json_iterator          begin() const;

  private:
    jsmn_parser            _parser;
    std::string            _js;
    std::vector<jsmntok_t> _tokens;

                           json_parser(json_parser const&);
    json_parser&           operator=(json_parser const&);
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_PARSER_HH
