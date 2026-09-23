#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::state::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
