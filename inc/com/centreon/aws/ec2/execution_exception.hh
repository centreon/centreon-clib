/*
** Copyright 2011-2015 Centreon
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

#ifndef CC_AWS_EC2_EXECUTION_EXCEPTION_HH
#  define CC_AWS_EC2_EXECUTION_EXCEPTION_HH

#  include <string>
#  include "com/centreon/exceptions/basic.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class parsing_exception parsing_exception.hh "com/centreon/aws/ec2/parsing_exception.hh"
     *  @brief an execution exception
     */
    class                    execution_exception : public exceptions::basic {
    public:
                             execution_exception();
                             execution_exception(
                               execution_exception const& other);
    execution_exception&     operator=(execution_exception const& other);
                             ~execution_exception() throw();
    private:
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_PARSING_EXCEPTION_HH
