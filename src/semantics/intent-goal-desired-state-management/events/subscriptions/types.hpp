#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::intent_goal_desired_state_management::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
