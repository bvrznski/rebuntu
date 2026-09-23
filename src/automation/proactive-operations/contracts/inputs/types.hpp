#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::proactive_operations::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
