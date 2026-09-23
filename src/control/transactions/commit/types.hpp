#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
