##
## Copyright 2011-2013 Merethis
##
## This file is part of Centreon Clib.
##
## Centreon Clib is free software: you can redistribute it
## and/or modify it under the terms of the GNU Affero General Public
## License as published by the Free Software Foundation, either version
## 3 of the License, or (at your option) any later version.
##
## Centreon Clib is distributed in the hope that it will be
## useful, but WITHOUT ANY WARRANTY; without even the implied warranty
## of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
## Affero General Public License for more details.
##
## You should have received a copy of the GNU Affero General Public
## License along with Centreon Clib. If not, see
## <http://www.gnu.org/licenses/>.
##

# Set directories.
set(SRC_DIR "${SRC_DIR}/json")
set(INC_DIR "${INC_DIR}/json")

# Set sources.
set(
  SOURCES
  ${SOURCES}
  "${SRC_DIR}/jsmn.c"
  "${SRC_DIR}/json_iterator.cc"
  "${SRC_DIR}/json_parser.cc"
  "${SRC_DIR}/json_writer.cc"
  "${SRC_DIR}/json_serializable.cc"
  "${SRC_DIR}/json_serializable_member.cc"
  PARENT_SCOPE
)

# Set headers.
set(
  HEADERS
  ${HEADERS}
  "${INC_DIR}/jsmn.h"
  "${INC_DIR}/json_iterator.hh"
  "${INC_DIR}/json_parser.hh"
  "${INC_DIR}/json_serializable.hh"
  "${INC_DIR}/json_serializable_member.hh"
  "${INC_DIR}/json_writer.hh"
  PARENT_SCOPE
)
