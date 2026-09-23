#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::resource_foundation::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
