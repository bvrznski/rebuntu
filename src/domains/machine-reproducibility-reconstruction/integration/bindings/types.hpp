#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::machine_reproducibility_reconstruction::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
