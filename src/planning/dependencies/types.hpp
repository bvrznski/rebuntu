#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::dependencies {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
