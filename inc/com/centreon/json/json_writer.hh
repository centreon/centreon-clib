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

#ifndef CC_JSON_JSON_WRITER_HH
#  define CC_JSON_JSON_WRITER_HH

#  include <string>
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace json {
  /**
   *  @class json_writer json_writer.hh "com/centreon/json/json_writer.hh"
   *  @brief Simple json writer.
   */
  class                    json_writer {
  public:
                           json_writer();
                           ~json_writer();

    std::string const&     get_string() const;

    void                   open_object();
    void                   close_object();
    void                   open_array();
    void                   close_array();
    void                   add_key(std::string const& key);
    void                   add_string(std::string const& str);
    void                   add_number(long long number);
    void                   add_null();
    void                   add_boolean(bool value);

  private:
    std::string            _string;

    void                   _put_comma();

                           json_writer(json_writer const&);
    json_writer&           operator=(json_writer const&);
  };
} // namespace json

CC_END()

#endif // !CC_JSON_JSON_WRITER_HH
