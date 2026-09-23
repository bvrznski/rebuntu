#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::resource_foundation::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
