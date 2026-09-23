#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::secrets_credentials_management::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
