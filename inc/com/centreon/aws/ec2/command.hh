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

#ifndef CC_AWS_EC2_COMMAND_HH
#  define CC_AWS_EC2_COMMAND_HH

#  include <string>
#  include "com/centreon/namespace.hh"
#  include "com/centreon/aws/ec2/spot_instance.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class command command.hh "com/centreon/aws/ec2/command.hh"
     *  @brief aws cli wrapper.
     */
    class                    command {
    public:
                             command(std::string const& profile);
                             ~command() throw();

     std::vector<spot_instance>
                             request_spot_instance(
                               unsigned int instance_count,
                               spot_instance const& instance);
     std::vector<spot_instance>
                             get_spot_instances();
     spot_instance::spot_instance_state
                             cancel_spot_instance_request(
                               std::string const& spot_instance_id);
     std::string             terminate_spot_instance(
                               std::string const& spot_instance_id);

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
