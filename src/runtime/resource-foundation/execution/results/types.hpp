#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::resource_foundation::execution::results {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
