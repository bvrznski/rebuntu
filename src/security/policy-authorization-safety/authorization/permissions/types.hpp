#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::policy_authorization_safety::authorization::permissions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
