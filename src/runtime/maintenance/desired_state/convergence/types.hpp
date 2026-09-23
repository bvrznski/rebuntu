#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::desired_state::convergence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
