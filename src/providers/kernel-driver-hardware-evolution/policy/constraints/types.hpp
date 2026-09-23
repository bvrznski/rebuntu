#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::kernel_driver_hardware_evolution::policy::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
