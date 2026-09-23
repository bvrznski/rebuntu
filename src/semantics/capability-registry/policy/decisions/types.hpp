#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::policy::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
