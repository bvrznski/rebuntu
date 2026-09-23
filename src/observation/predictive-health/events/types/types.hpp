#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
