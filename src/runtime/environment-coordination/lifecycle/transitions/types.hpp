#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::lifecycle::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
