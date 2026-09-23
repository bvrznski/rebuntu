#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
