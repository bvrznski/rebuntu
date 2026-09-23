#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::verification::evidence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
