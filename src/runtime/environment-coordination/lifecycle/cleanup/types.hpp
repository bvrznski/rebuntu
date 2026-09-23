#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::lifecycle::cleanup {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
