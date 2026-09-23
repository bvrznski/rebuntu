#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
