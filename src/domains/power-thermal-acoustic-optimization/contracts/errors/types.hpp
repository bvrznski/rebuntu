#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::power_thermal_acoustic_optimization::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
