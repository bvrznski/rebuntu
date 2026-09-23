#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
