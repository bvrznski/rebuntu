#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::secrets_credentials_management::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
