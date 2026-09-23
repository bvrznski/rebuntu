#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::semantic_administration::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
