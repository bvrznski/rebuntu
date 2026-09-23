#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::security::least_privilege {
struct LeastPrivilegeContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
