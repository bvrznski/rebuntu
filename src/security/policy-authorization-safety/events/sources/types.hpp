#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::policy_authorization_safety::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
