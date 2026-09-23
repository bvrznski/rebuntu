#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::evergreen_platform::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
