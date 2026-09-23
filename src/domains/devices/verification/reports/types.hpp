#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::devices::verification::reports {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
