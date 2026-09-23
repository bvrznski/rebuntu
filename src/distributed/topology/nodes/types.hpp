#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::topology::nodes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
