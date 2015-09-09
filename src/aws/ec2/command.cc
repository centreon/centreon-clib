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

#include <ctime>
#include <cstdlib>
#include <sstream>
#include "com/centreon/json/json_parser.hh"
#include "com/centreon/process.hh"
#include "com/centreon/aws/ec2/command.hh"
#include "com/centreon/misc/command_line_writer.hh"
#include "com/centreon/aws/ec2/execution_exception.hh"
#include "com/centreon/aws/ec2/parsing_exception.hh"

using namespace com::centreon::aws::ec2;

static unsigned int seed = 0;

/**
 *  Constructor.
 *
 *  @param[in] profile  The name of the profile that should be
 *                      used by the aws cli wrapper. Empty for the default
 *                      profile.
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
  _execute("aws help");
}

/**
 *  Request the creation of instances.
 *
 *  @param[in] spot_price      The spot price.
 *  @param[in] instance_count  How many instances.
 *  @param[in] type            The type of the instance.
 *  @param[in] valid_from      The start of the validity.
 *  @param[in] valid_until     The end of the validity.
 *  @param[in] spec            Launch specifications.
 *
 *  @return                    List of spot instances requested.
 */
std::vector<spot_instance> command::request_spot_instance(
                                      double spot_price,
                                      unsigned int instance_count,
                                      std::string const& type,
                                      timestamp valid_from,
                                      timestamp valid_until,
                                      launch_specification const& spec) {
  if (instance_count == 0)
    return (std::vector<spot_instance>());

  // Get args.
  json::json_writer js_spec;
  spec.serialize(js_spec);

  // Create command.
  misc::command_line_writer writer("aws ec2 request-spot-instances");

  writer.add_arg_condition("--profile", _profile, !_profile.empty());
  writer.add_arg("--spot-price", spot_price);
  writer.add_arg("--client-token", _generate_client_token());
  writer.add_arg_condition("--type", type, !type.empty());
  writer.add_arg_condition("--valid-from", valid_from, !valid_from.is_null());
  writer.add_arg_condition(
    "--valid-until",
    valid_until,
    !valid_until.is_null());
  writer.add_arg_condition(
    "--launch-specification",
    js_spec.get_string(),
    !spec.is_null());

  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  std::vector<spot_instance> ret;

  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "SpotInstanceRequests")
    throw (parsing_exception()
           << "command: request_spot_instance: "
              "couldn't parse json answer: expected"
              " 'SpotInstanceRequests', got '" << it.get_string() << "'");

  json::unserialize(ret, it.enter_children());
  return (ret);
}

/**
 *  Get all the spot instances currently requested.
 *
 *  @return  Vector of spot instances.
 */
std::vector<spot_instance> command::get_spot_instances() {
  misc::command_line_writer writer("aws ec2 describe-spot-instance-requests");

  writer.add_arg_condition("--profile", _profile, !_profile.empty());

  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  std::vector<spot_instance> ret;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "SpotInstanceRequests")
    throw (parsing_exception()
           << "command: get_spot_instances:"
              " couldn't parse json answer: expected"
              " 'SpotInstanceRequests', got '" << it.get_string() << "'");
  json::unserialize(ret, it.enter_children());
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

  writer.add_arg_condition("--profile", _profile, !_profile.empty());
  writer.add_arg("--spot-instance-request-ids", spot_instance_id);
  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "CancelledSpotInstanceRequests")
    throw (parsing_exception()
           << "command: cancel_spot_instance_request: "
              "couldn't parse json answer: expected "
              "'CancelledSpotInstanceRequests', got '" << it.get_string() << "'");
  it = it.enter_children().enter_children();
  if (it.get_string() != "State"
        && (it.enter_children()).get_type() != json::json_iterator::string)
    throw (parsing_exception()
           << "command: cancel_spot_instance_request: "
              "couldn't parse json answer");
  return (spot_instance::get_state_from_string(it.get_string()));
}

/**
 *  Get an instance from an instance id.
 *
 *  @param[in] instance_id  The instance id.
 *
 *  @return                 The instance.
 */
instance command::get_instance_from_id(
                    std::string const& instance_id) {
  misc::command_line_writer writer("aws ec2 describe-instances");

  writer.add_arg_condition("--profile", _profile, !_profile.empty());
  writer.add_arg("--instance-ids", instance_id);
  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "Reservations")
    throw (parsing_exception()
           << "command: get_instance_from_id: "
              "couldn't parse json answer: expected "
              "'Reservations', got '" << it.get_string() << "'");
  it = it.enter_children().enter_children()
         .find_child("Instances").enter_children().enter_children();
  instance res;
  json::unserialize(res, it);
  return (res);
}

/**
 *  Terminate an instance.
 *
 *  @param[in] spot_instance_id  The instance id to terminate.
 *
 *  @return                      The new state of the instance id.
 */
std::string command::terminate_instance(
                       std::string const& instance_id) {
  misc::command_line_writer writer("aws ec2 terminate-instances");

  writer.add_arg_condition("--profile", _profile, !_profile.empty());
  writer.add_arg("--instance-ids", instance_id);
  std::string return_string = _execute(writer.get_command());

  // Parse returned json.
  json::json_parser parser;
  parser.parse(return_string);
  json::json_iterator it = parser.begin().enter_children();
  if (it.get_string() != "TerminatingInstances")
    throw (parsing_exception()
           << "command: terminate_instance: "
              "couldn't parse json answer: expected "
              "'TerminatingInstances', got '" << it.get_string() << "'");
  it = it.enter_children().enter_children()
         .find_child("CurrentState").enter_children().find_child("Name");
  if (it.get_string() != "Name"
      && it.enter_children().get_type() != json::json_iterator::string)
    throw (parsing_exception()
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
    throw (execution_exception() << "error while executing aws: " << err);
  }

  std::string ret;
  proc.read(ret);

  return (ret);
}
