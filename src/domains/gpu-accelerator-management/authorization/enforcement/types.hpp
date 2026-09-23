#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::gpu_accelerator_management::authorization::enforcement {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
