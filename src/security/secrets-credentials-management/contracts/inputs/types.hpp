#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::secrets_credentials_management::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
