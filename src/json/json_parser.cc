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

#include "com/centreon/json/json_parser.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::json;

/**
 *  Constructor.
 */
json_parser::json_parser() {}

/**
 *  Destructor.
 */
json_parser::~json_parser() {}

/**
 *  Parse a json string.
 *
 *  @param[in] js  The json string.
 */
void json_parser::parse(std::string const& js) {
  ::jsmn_init(&_parser);

  // Get the number of tokens.
  jsmnerr_t ret = ::jsmn_parse(&_parser, js.c_str(), js.size(), NULL, 0);

  // An error has occured.
  if (ret < 0) {
    if (ret == JSMN_ERROR_INVAL)
      throw (exceptions::basic()
             << "couldn't parse json '"
             << js << "': invalid character inside js string");
    else if (ret == JSMN_ERROR_PART)
      throw (exceptions::basic()
             << "couldn't parse json '"
             << js << "': unexpected termination");
    else
      throw (exceptions::basic()
             << "couldn't parse json '"
             << js << "': unknown error");
  }

  _tokens.clear();
  _tokens.resize(ret);

  // Parse the tokens.
  ::jsmn_parse(&_parser, js.c_str(), js.size(), &_tokens[0], _tokens.size());

  _js = js;
}
