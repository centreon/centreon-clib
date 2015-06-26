/*
** Copyright 2011-2014 Merethis
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

#include <ctime>
#include <cstdlib>
#include <sstream>
#include "com/centreon/json/json_parser.hh"
#include "com/centreon/process.hh"
#include "com/centreon/aws/ec2/command.hh"
#include "com/centreon/misc/command_line_writer.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

static unsigned int seed = 0;

/**
 *  Constructor.
 *
 *  @param[in] profile  The name of the profile that should be
 *                      used by the aws cli wrapper.
 */
command::command(std::string const& profile)
  : _profile(profile) {
  _sanity_checks();
}

/**
 *  Destructor.
 */
command::~command() throw() {

}

/**
 *  Check that aws cli exists.
 */
void command::_sanity_checks() {
  process proc;
  proc.exec("aws help", _command_timeout);
  proc.wait();
  if (proc.exit_status() != process::normal || proc.exit_code() != 0) {
    std::string err;
    proc.read_err(err);
    throw (exceptions::basic() << "couldn't execute aws: " << err);
  }
}

/**
 *  Request the creation of an instance.
 *
 *  @param[in] instance  The instance.
 *
 *  @return              The instances requested.
 */
std::vector<spot_instance> command::request_spot_instance(
                                      unsigned int instance_count,
                                      spot_instance const& instance) {
  if (instance_count == 0)
    return (std::vector<spot_instance>());

  // Get args.
  double spot_price = instance.get_spot_price();
  std::string client_token = _generate_client_token();
  std::string type = instance.get_type();
  timestamp valid_from = instance.get_valid_from();
  timestamp valid_until = instance.get_valid_until();
  launch_specification const& spec = instance.get_launch_specification();
  json::json_writer js_spec;
  spec.serialize(js_spec);

  // Create command.
  misc::command_line_writer writer("aws ec2 request-spot-instances");

  writer.add_arg("--spot-price", spot_price);
  writer.add_arg("--client-toker", client_token);
  writer.add_arg("--type", type);
  writer.add_arg("--valid-from", valid_from);
  writer.add_arg("--valid-until", valid_until);
  writer.add_arg("--launch-specification", js_spec.get_string());

  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  std::vector<spot_instance> ret;

  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "SpotInstanceRequests")
    throw (exceptions::basic()
           << "command: request_spot_instance: "
              "couldn't parse json answer: expected"
              " 'SpotInstanceRequests', got '" << it.get_string() << "'");
  ++it;

  json::unserialize(ret, it);
  return (ret);
}

/**
 *  Get all the spot instances currently requested.
 *
 *  @return  Vector of spot instances.
 */
std::vector<spot_instance> command::get_spot_instances() {
  std::string return_string = _execute(
                                "aws ec2 describe-spot-instance-requests");
  // Parse returned json.
  json::json_parser parser;
  std::vector<spot_instance> ret;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "SpotInstanceRequests")
    throw (exceptions::basic()
           << "command: get_spot_instances:"
              " couldn't parse json answer: expected"
              " 'SpotInstanceRequests', got '" << it.get_string() << "'");
  ++it;
  json::unserialize(ret, it);
  return (ret);
}

/**
 *  Cancel a spot instance request.
 *
 *  Will not terminate the associated instance.
 *
 *  @param[in] spot_instance_id  The spot instance id to cancel.
 *
 *  @return                      The new state of the instance id.
 */
spot_instance::spot_instance_state command::cancel_spot_instance_request(
                                      std::string const& spot_instance_id) {
  misc::command_line_writer writer("aws ec2 cancel-spot-instance-requests");

  writer.add_arg("--spot-instance-request-ids", spot_instance_id);
  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "CancelledSpotInstanceRequests")
    throw (exceptions::basic()
           << "command: cancel_spot_instance_request: "
              "couldn't parse json answer: expected "
              "'CancelledSpotInstanceRequests', got '" << it.get_string() << "'");
  ++it;
  it = it.enter_children().enter_children();
  if (it.get_string() != "State"
        && (++it).get_type() != json::json_iterator::string)
    throw (exceptions::basic()
           << "command: cancel_spot_instance_request: "
              "couldn't parse json answer");
  return (spot_instance::get_state_from_string(it.get_string()));
}

/**
 *  Terminate the spot instance.
 *
 *  @param[in] spot_instance_id  The spot instance id to terminate.
 *
 *  @return                      The new state of the instance id.
 */
std::string command::terminate_spot_instance(
                       std::string const& spot_instance_id) {
  misc::command_line_writer writer("aws ec2 terminate-instances");

  writer.add_arg("--instance-ids", spot_instance_id);
  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "TerminatingInstances")
    throw (exceptions::basic()
           << "command: terminate_spot_instance: "
              "couldn't parse json answer: expected "
              "'TerminatingInstances', got '" << it.get_string() << "'");
  ++it;
  it = it.enter_children().find_child("CurrentState").find_child("Name");
  if (it.get_string() != "Name"
      && (++it).get_type() != json::json_iterator::string)
    throw (exceptions::basic()
           << "command: terminate_spot_instance: "
              "couldn't parse json answer");
  return (it.get_string());
}

/**
 *  Generate an unique client token.
 *
 *  @return  An unique client token.
 */
std::string command::_generate_client_token() const {
  std::ostringstream oss;

  if (seed == 0) {
    timestamp now = ::time(NULL);
    seed = (unsigned int)now.to_seconds();
    ::srandom(seed);
  }

  long random_value = ::random();
  oss << random_value;
  return (oss.str());
}

/**
 *  Execute a command.
 *
 *  @param[in] cmd  The command to execute.
 *
 *  @return         The return of the command.
 */
std::string command::_execute(std::string const& cmd) {
  process proc;
  proc.exec(cmd);
  proc.wait();

  if (proc.exit_status() != process::normal || proc.exit_code() != 0) {
    std::string err;
    proc.read_err(err);
    throw (exceptions::basic() << "couldn't execute aws: " << err);
  }

  std::string ret;
  proc.read(ret);

  return (ret);
}
