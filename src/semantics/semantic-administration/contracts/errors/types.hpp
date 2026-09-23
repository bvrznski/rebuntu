#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::semantic_administration::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
