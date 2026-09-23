#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
