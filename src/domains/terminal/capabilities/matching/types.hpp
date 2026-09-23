#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::terminal::capabilities::matching {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
