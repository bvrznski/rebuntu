#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::planning::rollback_plans {
struct RollbackPlansContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
