#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::continuous_reconciliation_goal_maintenance::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
