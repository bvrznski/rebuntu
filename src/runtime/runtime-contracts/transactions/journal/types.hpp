#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::runtime_contracts::transactions::journal {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
