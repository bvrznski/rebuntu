#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::verification::probes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
