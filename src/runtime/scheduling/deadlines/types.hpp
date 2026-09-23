#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::scheduling::deadlines {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
