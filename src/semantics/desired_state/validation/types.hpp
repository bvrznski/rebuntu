#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::desired_state::validation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
