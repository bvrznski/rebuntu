#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::platform_abstraction_portability_foundation::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
