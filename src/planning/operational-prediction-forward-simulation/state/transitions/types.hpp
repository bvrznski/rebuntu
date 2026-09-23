#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::operational_prediction_forward_simulation::state::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
