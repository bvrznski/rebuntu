#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::whole_system_integration::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
