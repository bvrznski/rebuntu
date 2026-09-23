#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_rebuntu_system::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
