#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::storage::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
