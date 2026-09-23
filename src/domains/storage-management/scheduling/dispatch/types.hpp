#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::storage_management::scheduling::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
