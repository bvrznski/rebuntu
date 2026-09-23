#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_goal_desired_state_coordination::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
