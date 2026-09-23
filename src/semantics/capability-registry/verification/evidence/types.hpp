#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::verification::evidence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
