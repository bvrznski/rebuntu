#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::evergreen_platform::verification::probes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
