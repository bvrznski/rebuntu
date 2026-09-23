#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::service_management::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
