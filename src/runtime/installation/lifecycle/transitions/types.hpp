#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::installation::lifecycle::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
