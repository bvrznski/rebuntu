#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::software::transactions::journal {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
