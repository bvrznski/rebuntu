#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::power_thermal_acoustic_optimization::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
