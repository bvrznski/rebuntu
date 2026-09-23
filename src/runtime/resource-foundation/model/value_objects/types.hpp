#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::resource_foundation::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
