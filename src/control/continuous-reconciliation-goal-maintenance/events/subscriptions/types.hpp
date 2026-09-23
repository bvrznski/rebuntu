#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::continuous_reconciliation_goal_maintenance::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
