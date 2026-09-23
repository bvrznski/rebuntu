#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::resource_intent_dynamic_allocation::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
