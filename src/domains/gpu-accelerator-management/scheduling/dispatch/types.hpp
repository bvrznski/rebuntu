#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::gpu_accelerator_management::scheduling::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
