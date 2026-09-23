#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::privilege_boundary_secure_execution::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
