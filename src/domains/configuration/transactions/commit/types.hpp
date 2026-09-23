#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::configuration::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
