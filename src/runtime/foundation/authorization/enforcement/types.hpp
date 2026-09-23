#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::authorization::enforcement {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
