#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::services::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
