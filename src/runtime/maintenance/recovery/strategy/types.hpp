#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
