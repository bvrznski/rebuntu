#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
