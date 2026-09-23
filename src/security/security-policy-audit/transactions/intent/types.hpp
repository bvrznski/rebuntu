#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::security_policy_audit::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
