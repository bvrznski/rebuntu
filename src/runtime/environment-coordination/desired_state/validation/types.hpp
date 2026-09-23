#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::desired_state::validation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
