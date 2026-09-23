#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::recovery::repair {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
