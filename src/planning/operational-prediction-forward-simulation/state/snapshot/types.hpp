#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::operational_prediction_forward_simulation::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
