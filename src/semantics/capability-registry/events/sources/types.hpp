#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
