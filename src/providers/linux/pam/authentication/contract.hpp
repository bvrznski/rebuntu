#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::pam::authentication {
struct AuthenticationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
