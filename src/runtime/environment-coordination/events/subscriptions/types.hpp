#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
