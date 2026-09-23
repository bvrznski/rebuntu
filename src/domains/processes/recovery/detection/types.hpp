#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::processes::recovery::detection {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
