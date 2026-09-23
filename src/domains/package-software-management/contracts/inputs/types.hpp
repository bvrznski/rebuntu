#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::package_software_management::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
