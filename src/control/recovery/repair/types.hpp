#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::recovery::repair {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
