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

#ifndef CC_AWS_EC2_SPOT_INSTANCE_STATUS_HH
#  define CC_AWS_EC2_SPOT_INSTANCE_STATUS_HH

#  include <string>
#  include <vector>
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/timestamp.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class spot_instance_status spot_instance_status.hh "com/centreon/aws/ec2/spot_instance_status.hh"
     *  @brief aws ec2 spot instance status wrapper.
     */
    class                    spot_instance_status : public json::json_serializable {
    public:
                             spot_instance_status();
                             spot_instance_status(
                               spot_instance_status const& other);
      virtual                ~spot_instance_status();
      spot_instance_status&  operator=(spot_instance_status const& other);

      timestamp              get_update_time() const;
      std::string const&     get_code() const;
      std::string const&     get_message() const;

      void                   set_update_time(std::string const& update);
      void                   set_code(std::string const& code);
      void                   set_message(std::string const& code);

      bool                   is_null() const;

    private:
      timestamp              _update_time;
      std::string            _code;
      std::string            _message;

      void                   _init_bindings();
      void                   _internal_copy(spot_instance_status const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_SPOT_INSTANCE_STATUS_HH
