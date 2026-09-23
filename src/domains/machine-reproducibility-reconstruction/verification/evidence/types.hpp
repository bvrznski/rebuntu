#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::verification::evidence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
