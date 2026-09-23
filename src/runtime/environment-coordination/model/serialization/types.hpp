#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_coordination::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
