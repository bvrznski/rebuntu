#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
