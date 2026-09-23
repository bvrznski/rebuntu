#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::lifecycle::states {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
