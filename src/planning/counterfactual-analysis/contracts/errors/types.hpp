#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::counterfactual_analysis::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
