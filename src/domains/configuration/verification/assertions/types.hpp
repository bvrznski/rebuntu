#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::configuration::verification::assertions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
