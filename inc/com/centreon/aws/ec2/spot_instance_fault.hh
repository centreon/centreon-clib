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

#ifndef CC_AWS_EC2_SPOT_INSTANCE_FAULT_HH
#  define CC_AWS_EC2_SPOT_INSTANCE_FAULT_HH

#  include <string>
#  include <vector>
#  include "com/centreon/timestamp.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class spot_instance_fault spot_instance_fault.hh "com/centreon/aws/ec2/spot_instance_fault.hh"
     *  @brief aws ec2 spot instance fault wrapper.
     */
    class                    spot_instance_fault {
    public:
                             spot_instance_fault();
                             ~spot_instance_fault();
                             spot_instance_fault(
                               spot_instance_fault const& other);
      spot_instance_fault&   operator=(spot_instance_fault const& other);

      std::string const&     get_code() const;
      std::string const&     get_message() const;

      void                   set_code(std::string const& code);
      void                   set_message(std::string const& message);

      bool                   is_null() const;

    private:
      std::string            _code;
      std::string            _message;

      void                   _internal_copy(spot_instance_fault const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_SPOT_INSTANCE_FAULT_HH
