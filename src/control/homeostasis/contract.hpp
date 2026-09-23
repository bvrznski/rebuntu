#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::control::homeostasis {
struct HomeostasisContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
