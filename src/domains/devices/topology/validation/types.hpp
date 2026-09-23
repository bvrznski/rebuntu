#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::devices::topology::validation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
