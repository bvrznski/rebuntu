#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::identity::desired_state::model {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
