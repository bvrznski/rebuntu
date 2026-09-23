#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::storage_management::lifecycle::hooks {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
