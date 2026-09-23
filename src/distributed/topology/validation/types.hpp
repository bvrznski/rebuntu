#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::topology::validation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
