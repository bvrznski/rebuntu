#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::contracts::invariants {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
