#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::configuration_management::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
