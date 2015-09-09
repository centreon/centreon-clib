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

#ifndef CC_AWS_EC2_NETWORK_INTERFACE_HH
#  define CC_AWS_EC2_NETWORK_INTERFACE_HH

#  include <string>
#  include <vector>
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class network_interface network_interface.hh "com/centreon/aws/ec2/network_interface.hh"
     *  @brief aws network interface wrapper.
     */
    class                    network_interface : public json::json_serializable {
    public:
                             network_interface();
                             network_interface(
                               network_interface const& other);
    network_interface&       operator=(network_interface const& other);
                             ~network_interface();
    private:
      std::string            _network_interface_id;
      unsigned int           _device_index;
      std::string            _subnet_id;
      std::string            _description;
      std::string            _private_ip_address;
      std::vector<std::string>
                             _groups;
      bool                   _delete_on_termination;

      struct                  private_ip_address : public json::json_serializable {
                              private_ip_address();
                              private_ip_address(private_ip_address const& other);
        private_ip_address&   operator=(private_ip_address const& other);
        std::string           private_ip_address_value;
        bool                  primary;
      private:
        void                  _init_bindings();
      };

      std::vector<private_ip_address>
                             _private_ip_addresses;
      unsigned int           _secondary_private_ip_address_count;
      bool                   _associate_ip_address;

      void                   _init_bindings();
      void                   _internal_copy(network_interface const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_NETWORK_INTERFACE_HH
