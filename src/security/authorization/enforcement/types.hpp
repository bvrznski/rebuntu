#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::authorization::enforcement {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
