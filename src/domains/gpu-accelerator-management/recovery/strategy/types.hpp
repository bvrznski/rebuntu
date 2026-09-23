#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::gpu_accelerator_management::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
