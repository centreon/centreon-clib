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
#include "com/centreon/misc/stringifier.hh"

using namespace com::centreon::misc;

/**
 *  Check the stringifier insert long long.
 *
 *  @return 0 on success.
 */
int main() {
  stringifier buffer;
  buffer << static_cast<long long>(LLONG_MIN);
  buffer << static_cast<long long>(LLONG_MAX);

  std::ostringstream oss;
  oss << LLONG_MIN << LLONG_MAX;
  return (strcmp(buffer.data(), oss.str().c_str()));
}
