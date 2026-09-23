#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::workflow_foundation::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
