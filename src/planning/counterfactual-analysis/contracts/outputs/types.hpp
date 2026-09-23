#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::counterfactual_analysis::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
