#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::ownership::manifest {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
