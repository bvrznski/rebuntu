#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::health::recovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
