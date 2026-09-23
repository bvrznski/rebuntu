#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capabilities::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
