/*
** Copyright 2011-2014 Centreon
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
