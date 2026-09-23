#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::security_policy_audit::lifecycle::states {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
