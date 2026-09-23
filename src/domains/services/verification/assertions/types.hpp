#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::services::verification::assertions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
