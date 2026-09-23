#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::verification::reports {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
