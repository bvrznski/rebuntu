#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::gpu_accelerator_management::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
