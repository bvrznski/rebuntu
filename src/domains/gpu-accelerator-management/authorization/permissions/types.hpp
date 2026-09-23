#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::gpu_accelerator_management::authorization::permissions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
