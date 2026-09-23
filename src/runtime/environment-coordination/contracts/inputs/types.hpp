#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
