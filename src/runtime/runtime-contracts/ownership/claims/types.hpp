#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::runtime_contracts::ownership::claims {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
