#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::pam::account {
struct AccountContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
