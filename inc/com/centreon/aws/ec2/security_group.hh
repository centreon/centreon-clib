/*
** Copyright 2011-2013 Centreon
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
