#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::counterfactual_analysis::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
