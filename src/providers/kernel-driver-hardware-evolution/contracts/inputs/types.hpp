#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::kernel_driver_hardware_evolution::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
