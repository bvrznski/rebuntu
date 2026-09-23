#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::semantic_administration::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
