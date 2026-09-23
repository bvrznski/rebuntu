#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
