#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::resource_management::lifecycle::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
