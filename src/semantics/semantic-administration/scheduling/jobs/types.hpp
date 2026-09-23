#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::semantic_administration::scheduling::jobs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
