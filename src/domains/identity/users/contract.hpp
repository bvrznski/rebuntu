#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::identity::users {
struct UsersContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
