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
set(SRC_DIR "${SRC_DIR}/aws")
set(INC_DIR "${INC_DIR}/aws")

# Set sources.
set(
  SOURCES
  ${SOURCES}
  "${SRC_DIR}/ec2/block_device_mapping.cc"
  "${SRC_DIR}/ec2/command.cc"
  "${SRC_DIR}/ec2/execution_exception.cc"
  "${SRC_DIR}/ec2/launch_specification.cc"
  "${SRC_DIR}/ec2/network_interface.cc"
  "${SRC_DIR}/ec2/parsing_exception.cc"
  "${SRC_DIR}/ec2/instance.cc"
  "${SRC_DIR}/ec2/security_group.cc"
  "${SRC_DIR}/ec2/spot_instance.cc"
  "${SRC_DIR}/ec2/spot_instance_fault.cc"
  "${SRC_DIR}/ec2/spot_instance_status.cc"
  PARENT_SCOPE
)

# Set headers.
set(
  HEADERS
  ${HEADERS}
  "${INC_DIR}/ec2/block_device_mapping.hh"
  "${INC_DIR}/ec2/command.hh"
  "${INC_DIR}/ec2/execution_exception.hh"
  "${INC_DIR}/ec2/network_interface.hh"
  "${INC_DIR}/ec2/launch_specification.hh"
  "${INC_DIR}/ec2/parsing_exception.hh"
  "${INC_DIR}/ec2/instance.hh"
  "${INC_DIR}/ec2/security_group.hh"
  "${INC_DIR}/ec2/spot_instance.hh"
  "${INC_DIR}/ec2/spot_instance_fault.hh"
  "${INC_DIR}/ec2/spot_instance_status.hh"
  PARENT_SCOPE
)
