#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::terminal::capabilities::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
