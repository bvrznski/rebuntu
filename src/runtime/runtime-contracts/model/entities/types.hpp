#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::runtime_contracts::model::entities {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
