#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::operational_prediction_forward_simulation::scheduling::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
