#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::operational_prediction_forward_simulation::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
