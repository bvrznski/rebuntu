#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::privilege_boundary_secure_execution::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
