#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::software::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
