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
