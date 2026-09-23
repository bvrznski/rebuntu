#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::verification::reports {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
