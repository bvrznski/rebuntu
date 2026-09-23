#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::verification::evidence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
