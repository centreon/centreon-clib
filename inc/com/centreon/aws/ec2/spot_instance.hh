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

#ifndef CC_AWS_EC2_SPOT_INSTANCE_HH
#  define CC_AWS_EC2_SPOT_INSTANCE_HH

#  include <memory>
#  include <string>
#  include <vector>
#  include "com/centreon/timestamp.hh"
#  include "com/centreon/aws/ec2/launch_specification.hh"
#  include "com/centreon/aws/ec2/spot_instance_fault.hh"
#  include "com/centreon/aws/ec2/spot_instance_status.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class spot_instance spot_instance.hh "com/centreon/aws/ec2/spot_instance.hh"
     *  @brief aws ec2 spot instance wrapper.
     */
    class                    spot_instance {
    public:
                             spot_instance();
                             ~spot_instance();
                             spot_instance(spot_instance const& other);
      spot_instance&         operator=(spot_instance const& other);
    private:
      spot_instance_fault    _fault;
      spot_instance_status   _status;
      launch_specification   _launch_specification;
      timestamp              _valid_from;
      timestamp              _valid_until;
      std::string            _launch_group;
      std::string            _availability_zone_group;
      std::string            _product_description;
      std::string            _instance_id;
      std::string            _spot_instance_request_id;
      std::string            _state;
      std::string            _launched_availability_zone;
      std::string            _type;
      timestamp              _create_time;
      double                 _spot_price;

      void                   _internal_copy(spot_instance const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_SPOT_INSTANCE_HH
