#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::services::health::degradation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
