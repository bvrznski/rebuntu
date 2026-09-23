#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::authorization::principals {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
