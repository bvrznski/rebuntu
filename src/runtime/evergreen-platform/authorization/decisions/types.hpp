#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::evergreen_platform::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
