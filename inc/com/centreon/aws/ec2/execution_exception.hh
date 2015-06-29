/*
** Copyright 2011-2015 Merethis
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
