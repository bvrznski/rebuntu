#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
