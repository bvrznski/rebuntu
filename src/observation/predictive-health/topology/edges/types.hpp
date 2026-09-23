#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::topology::edges {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
