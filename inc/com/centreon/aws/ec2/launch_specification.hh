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

#ifndef CC_AWS_EC2_LAUNCH_SPECIFICATION_HH
#  define CC_AWS_EC2_LAUNCH_SPECIFICATION_HH

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
     *  @class launch_specification launch_specification.hh "com/centreon/aws/ec2/launch_specification.hh"
     *  @brief aws ec2 launch specification structure wrapper.
     */
    class                    launch_specification : public json::json_serializable {
    public:
                             launch_specification();
                             ~launch_specification();
                             launch_specification(
                               launch_specification const& other);
      launch_specification&  operator=(launch_specification const& other);

    private:
      std::string            _image_id;
      std::string            _key_name;

      struct                 security_group : public json::json_serializable {
                             security_group();
                             security_group(security_group const& other);
        security_group&      operator=(security_group const& other);
                             ~security_group();
        std::string          group_name;
        std::string          group_id;
      private:
        void                 _init_bindings();
      };
      std::vector<security_group>
                             _security_groups;

      std::string            _user_data;
      std::string            _instance_type;
      std::string            _placement_availability_zone;
      std::string            _placement_group_name;
      std::string            _kernel_id;
      std::string            _ramdisk_id;
      std::vector<block_device_mapping>
                             _block_device_mappings;
      std::string            _subnet_id;
      std::vector<network_interface>
                             _network_interfaces;
      std::string            _iam_instance_profile_arn;
      std::string            _iam_instance_profile_name;
      bool                   _ebs_optimized;
      bool                   _monitoring_enabled;

      void                   _init_bindings();
      void                   _internal_copy(launch_specification const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_LAUNCH_SPECIFICATION_HH
