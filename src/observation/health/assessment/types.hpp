#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::health::assessment {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
