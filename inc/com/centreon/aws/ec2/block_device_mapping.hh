/*
** Copyright 2015 Centreon
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

#ifndef CC_AWS_EC2_BLOCK_DEVICE_MAPPING_HH
#  define CC_AWS_EC2_BLOCK_DEVICE_MAPPING_HH

#  include <string>
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class block_device_mapping block_device_mapping.hh "com/centreon/aws/ec2/block_device_mapping.hh"
     *  @brief aws block device mapping wrapper.
     */
    class                    block_device_mapping : public json::json_serializable {
    public:
                             block_device_mapping();
                             block_device_mapping(
                               block_device_mapping const& other);
    virtual                  ~block_device_mapping();
    block_device_mapping&    operator=(block_device_mapping const& other);

    private:
      std::string            _virtual_name;
      std::string            _device_name;

      struct                 ebs : public json::json_serializable {
                             ebs();
                             ebs(ebs const& other);
        virtual              ~ebs();
        ebs&                 operator=(ebs const& other);
        std::string          status;
        std::string          snapshot_id;
        std::string          volume_size;
        bool                 delete_on_termination;
        std::string          volume_type;
        std::string          volume_id;
        timestamp            attach_time;
        unsigned int         lops;
        bool                 encrypted;

        bool                 is_null() const;
      private:
        void                 _init_bindings();
        void                 _internal_copy(ebs const& other);
      };
      ebs                    _ebs;
      std::string            _no_device;

      void                   _init_bindings();
      void                   _internal_copy(block_device_mapping const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_BLOCK_DEVICE_MAPPING_HH
