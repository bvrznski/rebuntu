#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::resource_management::policy::rules {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
