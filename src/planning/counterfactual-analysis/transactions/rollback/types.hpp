#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::counterfactual_analysis::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
