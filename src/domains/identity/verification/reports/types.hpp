#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::identity::verification::reports {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
