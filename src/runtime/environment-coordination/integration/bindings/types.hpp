#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
