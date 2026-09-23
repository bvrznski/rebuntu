#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::semantic_administration::state::persistence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
