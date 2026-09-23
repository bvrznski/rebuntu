#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::kernel_driver_hardware_evolution::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
