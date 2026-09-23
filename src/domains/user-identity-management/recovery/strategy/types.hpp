#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::user_identity_management::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
