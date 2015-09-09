##
## Copyright 2011-2013 Centreon
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
## For more information : contact@centreon.com
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
