#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::kernel::capabilities::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
