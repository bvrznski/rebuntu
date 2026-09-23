#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::predictive_health::events::routing {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
