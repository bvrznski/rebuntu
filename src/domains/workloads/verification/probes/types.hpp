#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::workloads::verification::probes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
