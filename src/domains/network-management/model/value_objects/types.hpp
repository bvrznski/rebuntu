#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::network_management::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
