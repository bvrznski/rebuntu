#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
