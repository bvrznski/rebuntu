#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::policy_authorization_safety::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
