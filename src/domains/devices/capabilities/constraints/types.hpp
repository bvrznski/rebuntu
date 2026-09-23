#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::devices::capabilities::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
