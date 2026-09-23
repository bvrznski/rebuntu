#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_goal_desired_state_coordination::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
