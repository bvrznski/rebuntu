#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
