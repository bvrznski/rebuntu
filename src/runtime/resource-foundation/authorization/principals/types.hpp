#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::resource_foundation::authorization::principals {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
