#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::resource_intent_dynamic_allocation::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
