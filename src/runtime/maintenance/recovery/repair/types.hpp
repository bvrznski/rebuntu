#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::recovery::repair {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
