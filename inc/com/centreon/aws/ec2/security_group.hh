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

#ifndef CC_AWS_EC2_SECURITY_GROUP_HH
#  define CC_AWS_EC2_SECURITY_GROUP_HH

#  include <memory>
#  include <string>
#  include <vector>
#  include "com/centreon/aws/ec2/network_interface.hh"
#  include "com/centreon/aws/ec2/block_device_mapping.hh"
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class security_group security_group.hh "com/centreon/aws/ec2/security_group.hh"
     *  @brief aws ec2 security group structure wrapper.
     *
     */
    class                 security_group : public json::json_serializable {
    public:
                          security_group();
                          security_group(security_group const& other);
     security_group&      operator=(security_group const& other);
                          ~security_group();

     std::string const&   get_group_name() const throw();
     std::string const&   get_group_id() const throw();

     void                 set_group_name(std::string const& val);
     void                 set_group_id(std::string const& val);

     void                 serialize(json::json_writer& writer) const;

     private:
       std::string        group_name;
       std::string        group_id;
       void               _init_bindings();
   };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_SECURITY_GROUP_HH
