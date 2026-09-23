#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::accelerators::capabilities::discovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
