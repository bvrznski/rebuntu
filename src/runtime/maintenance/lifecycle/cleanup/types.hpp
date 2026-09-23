#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::lifecycle::cleanup {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
