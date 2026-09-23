#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::core_runtime::integration::adapters {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
