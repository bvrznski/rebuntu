#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::scheduling::jobs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
