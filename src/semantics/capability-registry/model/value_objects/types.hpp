#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
