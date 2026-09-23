#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_foundation::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
