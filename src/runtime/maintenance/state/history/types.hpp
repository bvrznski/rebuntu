#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::state::history {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
