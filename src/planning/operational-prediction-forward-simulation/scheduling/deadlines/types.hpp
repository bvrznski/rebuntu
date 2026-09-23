#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::operational_prediction_forward_simulation::scheduling::deadlines {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
