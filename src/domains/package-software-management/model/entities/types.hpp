#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::package_software_management::model::entities {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
