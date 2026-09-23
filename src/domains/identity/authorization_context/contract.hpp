#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::identity::authorization_context {
struct AuthorizationContextContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
