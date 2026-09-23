#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::whole_system_integration::lifecycle::states {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
