#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::logs::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
