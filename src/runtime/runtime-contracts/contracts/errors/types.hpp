#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::runtime_contracts::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
