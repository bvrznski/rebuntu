#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::processes::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
