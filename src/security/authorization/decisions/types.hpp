#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
