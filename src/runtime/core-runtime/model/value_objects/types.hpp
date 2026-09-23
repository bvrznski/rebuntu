#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::core_runtime::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
