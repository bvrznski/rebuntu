#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::lifecycle::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
