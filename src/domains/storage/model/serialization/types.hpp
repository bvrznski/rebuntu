#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::storage::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
