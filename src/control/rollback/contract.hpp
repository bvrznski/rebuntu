#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::control::rollback {
struct RollbackContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
