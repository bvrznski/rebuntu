#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::service_management::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
