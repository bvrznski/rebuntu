#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::policy_authorization_safety::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
