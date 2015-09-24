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

#ifndef CC_AWS_EC2_INSTANCE_HH
#  define CC_AWS_EC2_INSTANCE_HH

#  include <memory>
#  include <string>
#  include <vector>
#  include "com/centreon/timestamp.hh"
#  include "com/centreon/aws/ec2/launch_specification.hh"
#  include "com/centreon/aws/ec2/block_device_mapping.hh"
#  include "com/centreon/aws/ec2/network_interface.hh"
#  include "com/centreon/aws/ec2/security_group.hh"
#  include "com/centreon/aws/ec2/spot_instance_status.hh"
#  include "com/centreon/json/json_iterator.hh"
#  include "com/centreon/json/json_writer.hh"
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class spot_instance spot_instance.hh "com/centreon/aws/ec2/spot_instance.hh"
     *  @brief aws ec2 instance wrapper.
     */
    class                    instance : public json::json_serializable {
    public:
                             instance();
                             ~instance();
                             instance(instance const& other);
      instance&              operator=(instance const& other);

      class                  product_code : public json::json_serializable {
      public:
                             product_code();
                             product_code(product_code const& other);
        product_code&        operator=(product_code const& other);
                             ~product_code();

        std::string          _product_code_id;
        std::string          _product_code_type;

      private:
        void                 _init_bindings();
      };

      enum                    instance_status {
                              pending = 0,
                              running,
                              shutting_down,
                              terminated,
                              stopping,
                              stopped,
                              rebooting,
                              unknown
      };

      std::string const&     get_instance_id() const throw();
      instance_status        get_instance_status() const throw();
      std::string const&     get_public_ip_address() const throw();
      std::string const&     get_private_ip_address() const throw();

    private:
      std::string            _instance_id;
      std::string            _image_id;
      unsigned int           _state_code;
      std::string            _state_name;
      std::string            _private_dns_name;
      std::string            _public_dns_name;
      std::string            _state_transition_reason;
      std::string            _key_name;
      unsigned int           _ami_launch_index;
      std::vector<product_code>
                             _product_codes;
      std::string            _instance_type;
      std::string            _placement_availability_zone;
      std::string            _placement_group_name;
      std::string            _placement_tenancy;
      std::string            _kernel_id;
      std::string            _ramdisk_id;
      std::string            _platform;
      std::string            _monitoring_state;
      std::string            _subnet_id;
      std::string            _vpc_id;
      std::string            _private_ip_address;
      std::string            _public_ip_address;
      std::string            _state_reason_code;
      std::string            _state_reason_message;
      std::string            _architecture;
      std::string            _root_device_type;
      std::string            _root_device_name;
      std::vector<block_device_mapping>
                             _block_device_mappings;
      std::string            _virtualization_type;
      std::string            _instance_lifecycle;
      std::string            _spot_instance_request_id;
      std::string            _client_token;
      std::vector<security_group>
                             _security_groups;
      bool                   _source_dest_check;
      std::string            _hypervisor;
      std::string            _iam_instance_profile_arn;
      std::string            _iam_instance_profile_id;
      std::string            _iam_instance_id;
      bool                   _ebs_optimized;
      std::string            _sriov_net_support;
      timestamp              _launch_time;

      void                   _init_bindings();
      void                   _internal_copy(instance const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_INSTANCE_HH
