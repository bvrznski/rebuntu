#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::lifecycle::cleanup {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
