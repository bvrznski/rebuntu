#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
