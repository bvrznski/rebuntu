#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_goal_desired_state_coordination::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
