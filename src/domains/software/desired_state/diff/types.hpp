#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::software::desired_state::diff {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
