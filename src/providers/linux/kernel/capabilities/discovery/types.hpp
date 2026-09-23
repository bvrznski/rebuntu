#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::kernel::capabilities::discovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
