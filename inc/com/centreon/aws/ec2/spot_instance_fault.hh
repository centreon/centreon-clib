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

#ifndef CC_AWS_EC2_SPOT_INSTANCE_FAULT_HH
#  define CC_AWS_EC2_SPOT_INSTANCE_FAULT_HH

#  include <string>
#  include <vector>
#  include "com/centreon/timestamp.hh"
#  include "com/centreon/namespace.hh"
#  include "com/centreon/json/json_serializable.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class spot_instance_fault spot_instance_fault.hh "com/centreon/aws/ec2/spot_instance_fault.hh"
     *  @brief aws ec2 spot instance fault wrapper.
     */
    class                    spot_instance_fault : public json::json_serializable {
    public:
                             spot_instance_fault();
                             spot_instance_fault(
                               spot_instance_fault const& other);
      virtual                ~spot_instance_fault();
      spot_instance_fault&   operator=(spot_instance_fault const& other);

      std::string const&     get_code() const;
      std::string const&     get_message() const;

      void                   set_code(std::string const& code);
      void                   set_message(std::string const& message);

      bool                   is_null() const;

    private:
      std::string            _code;
      std::string            _message;

      void                   _init_bindings();
      void                   _internal_copy(spot_instance_fault const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_SPOT_INSTANCE_FAULT_HH
