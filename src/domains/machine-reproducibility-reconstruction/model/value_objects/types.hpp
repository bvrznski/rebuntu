#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
