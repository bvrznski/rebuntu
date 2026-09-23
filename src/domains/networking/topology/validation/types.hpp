#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::networking::topology::validation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
