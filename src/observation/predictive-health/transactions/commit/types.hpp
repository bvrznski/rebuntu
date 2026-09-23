#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
