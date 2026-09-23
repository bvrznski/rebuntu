#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::devices::desired_state::diff {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
