#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::lifecycle::states {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
