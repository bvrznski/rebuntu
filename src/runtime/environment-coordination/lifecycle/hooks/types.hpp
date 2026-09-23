#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::lifecycle::hooks {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
