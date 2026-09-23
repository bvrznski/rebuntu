#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
