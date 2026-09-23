#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::networking::topology::discovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
