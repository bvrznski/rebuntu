#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
