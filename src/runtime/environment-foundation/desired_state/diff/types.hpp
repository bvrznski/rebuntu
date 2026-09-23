#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_foundation::desired_state::diff {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
