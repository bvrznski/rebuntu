#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
