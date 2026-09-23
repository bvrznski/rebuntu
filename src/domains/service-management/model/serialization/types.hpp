#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::service_management::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
