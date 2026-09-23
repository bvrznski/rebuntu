#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::networking::verification::assertions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
