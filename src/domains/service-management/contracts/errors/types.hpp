#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::service_management::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
