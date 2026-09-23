#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::policy::rules {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
