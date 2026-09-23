#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::package_software_management::verification::probes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
