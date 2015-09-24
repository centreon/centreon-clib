/*
** Copyright 2011-2014 Centreon
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

#include "com/centreon/aws/ec2/execution_exception.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
execution_exception::execution_exception() {

}

/**
 *  Copy constructor.
 *
 *   @param[in] other  The object to copy.
 */
execution_exception::execution_exception(
                       execution_exception const& other)
  : exceptions::basic(other) {
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  The object to copy.
 *
 *  @return           Reference to this object.
 */
execution_exception& execution_exception::operator=(
                       execution_exception const& other) {
  exceptions::basic::operator=(other);
  return (*this);
}

/**
 *  Destructor.
 */
execution_exception::~execution_exception() throw() {

}
