#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::storage_management::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
