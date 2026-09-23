#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::service_management::desired_state::convergence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
