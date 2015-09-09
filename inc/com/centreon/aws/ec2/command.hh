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

#ifndef CC_AWS_EC2_COMMAND_HH
#  define CC_AWS_EC2_COMMAND_HH

#  include <string>
#  include "com/centreon/namespace.hh"
#  include "com/centreon/aws/ec2/spot_instance.hh"
#  include "com/centreon/aws/ec2/instance.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class command command.hh "com/centreon/aws/ec2/command.hh"
     *  @brief aws cli wrapper.
     */
    class                    command {
    public:
                             command(std::string const& profile
                                      = std::string());
                             ~command() throw();

     std::vector<spot_instance>
                             request_spot_instance(
                               double spot_price,
                               unsigned int instance_count,
                               std::string const& type,
                               timestamp valid_from,
                               timestamp valid_until,
                               launch_specification const& spec);
     std::vector<spot_instance>
                             get_spot_instances();
     spot_instance::spot_instance_state
                             cancel_spot_instance_request(
                               std::string const& spot_instance_id);
     instance                get_instance_from_id(
                               std::string const& instance_id);
     std::string             terminate_instance(
                               std::string const& instance_id);

    private:
      static const unsigned int
                             _command_timeout = 3;

      std::string            _profile;

      void                   _sanity_checks();
      std::string            _generate_client_token() const;
      std::string            _execute(std::string const& cmd);

                             command(command const&);
      command&               operator=(command const&);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_COMMAND_HH
