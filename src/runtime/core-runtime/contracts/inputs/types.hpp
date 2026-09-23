#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::core_runtime::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
