#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::devices::health::recovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
