#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::lifecycle::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
