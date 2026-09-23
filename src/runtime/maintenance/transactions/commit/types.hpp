#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
