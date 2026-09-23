#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::security_policy_audit::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
