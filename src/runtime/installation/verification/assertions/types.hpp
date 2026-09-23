#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::installation::verification::assertions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
