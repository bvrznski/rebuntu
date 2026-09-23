#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::long_horizon_operational_planning::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
