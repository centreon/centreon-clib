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

#ifndef CC_MISC_ARGUMENT_HH
#  define CC_MISC_ARGUMENT_HH

#  include <list>
#  include <string>
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace              misc {
  /**
   *  @class argument argument.hh "com/centreon/misc/argument.hh"
   *  @brief Define class argument for get options.
   *
   *  This is an argument class.
   */
  class                argument {
  public:
    enum value_number {
      none = 0,
      one,
      multiple
    };

                       argument(
                         std::string const& long_name = "",
                         char name = '\0',
                         std::string const& description = "",
                         value_number has_value = none);
                       argument(argument const& other);
                       ~argument() throw ();
    argument&          operator=(argument const& other);
    bool               operator==(argument const& other) const throw ();
    bool               operator!=(argument const& other) const throw ();
    void               add_value(std::string const& value);
    std::string const& get_description() const throw ();
    value_number       get_has_value() const throw ();
    std::string const& get_long_name() const throw ();
    char               get_name() const throw ();
    std::list<std::string> const&
                       get_values() const throw ();
    bool               is_set() const throw ();
    void               set_description(std::string const& description);
    void               set_has_value(value_number val) throw ();
    void               set_long_name(std::string const& long_name);
    void               set_name(char name);

  private:
    argument&          _internal_copy(argument const& other);

    std::string        _description;
    value_number       _has_value;
    std::string        _long_name;
    char               _name;
    std::list<std::string>
                       _values;
  };
}

CC_END()

#endif // !CC_MISC_ARGUMENT_HH
