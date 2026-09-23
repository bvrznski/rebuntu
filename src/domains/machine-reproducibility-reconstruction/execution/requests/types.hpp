#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
