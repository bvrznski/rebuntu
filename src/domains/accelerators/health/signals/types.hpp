#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::accelerators::health::signals {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
