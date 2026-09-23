#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::continuous_reconciliation_goal_maintenance::transactions::journal {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
