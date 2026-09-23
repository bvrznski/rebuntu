#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::security::lsm {
struct LsmContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
