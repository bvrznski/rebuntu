#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
