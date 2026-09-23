#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::resource_management::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
