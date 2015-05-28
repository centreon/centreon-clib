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

#ifndef CC_AWS_EC2_BLOCK_DEVICE_MAPPING_HH
#  define CC_AWS_EC2_BLOCK_DEVICE_MAPPING_HH

#  include <string>
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class block_device_mapping block_device_mapping.hh "com/centreon/aws/ec2/block_device_mapping.hh"
     *  @brief aws block device mapping wrapper.
     */
    class                    block_device_mapping {
    public:
                             block_device_mapping();
                             block_device_mapping(
                               block_device_mapping const& other);
    block_device_mapping&    operator=(block_device_mapping const& other);
                             ~block_device_mapping();
    private:
      std::string            _virtual_name;
      std::string            _device_name;
      std::string            _ebs_snapshot_id;
      std::string            _ebs_volume_size;
      std::string            _ebs_delete_on_termination;
      std::string            _ebs_volume_type;
      unsigned int           _ebs_lops;
      bool                   _ebs_encrypted;
      std::string            _no_device;

      void                   _internal_copy(block_device_mapping const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_BLOCK_DEVICE_MAPPING_HH
