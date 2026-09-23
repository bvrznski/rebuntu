#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::recovery::detection {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
