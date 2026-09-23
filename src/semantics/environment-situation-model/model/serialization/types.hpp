#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::environment_situation_model::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
