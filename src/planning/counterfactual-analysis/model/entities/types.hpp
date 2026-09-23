#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::counterfactual_analysis::model::entities {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
