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

#include <limits.h>
#include <string.h>
#include <sstream>
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::exceptions;

/**
 *  Check the basic insert int.
 *
 *  @return 0 on success.
 */
int main() {
  basic ex;
  ex << static_cast<int>(INT_MIN);
  ex << static_cast<int>(INT_MAX);

  std::ostringstream oss;
  oss << INT_MIN << INT_MAX;
  return (strcmp(ex.what(), oss.str().c_str()));
}
