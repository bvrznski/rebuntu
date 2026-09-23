#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
