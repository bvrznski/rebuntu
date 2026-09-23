#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::state::history {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
