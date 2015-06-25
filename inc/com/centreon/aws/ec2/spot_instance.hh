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
#  include "com/centreon/json/json_iterator.hh"
#  include "com/centreon/json/json_writer.hh"
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class spot_instance spot_instance.hh "com/centreon/aws/ec2/spot_instance.hh"
     *  @brief aws ec2 spot instance wrapper.
     */
    class                    spot_instance : public json::json_serializable {
    public:
                             spot_instance();
                             ~spot_instance();
                             spot_instance(spot_instance const& other);
      spot_instance&         operator=(spot_instance const& other);

      enum                   spot_instance_state {
        open = 0,
        failed,
        active,
        canceled,
        closed,
        unknown
      };

      spot_instance_fault const&
                             get_fault() const throw();
      spot_instance_status const&
                             get_status() const throw();
      launch_specification const&
                             get_launch_specification() const throw();
      timestamp              get_valid_from() const throw();
      timestamp              get_valid_until() const throw();
      std::string const&     get_launch_group() const throw();
      std::string const&     get_availability_zone_group() const throw();
      std::string const&     get_product_description() const throw();
      std::string const&     get_instance_id() const throw();
      std::string const&     get_spot_instance_request_id() const throw();
      std::string const&     get_state_string() const throw();
      spot_instance_state    get_state() const throw();
      std::string const&     get_launched_availability_zone() const throw();
      std::string const&     get_type() const throw();
      timestamp              get_create_time() const throw();
      double                 get_spot_price() const throw();

      void                   set_fault(spot_instance_fault const& fault);
      void                   set_status(spot_instance_status const& status);
      void                   set_launch_specification(launch_specification const& val);
      void                   set_valid_from(timestamp valid_from);
      void                   set_valid_until(timestamp valid_until);
      void                   set_launch_group(std::string const& launch_group);
      void                   set_availability_zone_groupe(std::string const& val);
      void                   set_product_description(std::string const& val);
      void                   set_instance_id(std::string const& instance_id);
      void                   set_spot_instance_request_id(std::string const& val);
      void                   set_state(std::string const& state);
      void                   set_state(spot_instance_state const& state);
      void                   set_launched_availability_zone(std::string const& val);
      void                   set_type(std::string const& type);
      void                   set_create_time(timestamp create_time);
      void                   set_spot_price(double spot_price);

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

      void                   _init_bindings();
      void                   _internal_copy(spot_instance const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_SPOT_INSTANCE_HH
