#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::security::secrets_policy {
struct SecretsPolicyContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
