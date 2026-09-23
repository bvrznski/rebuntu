#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::storage::recovery {
struct RecoveryContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
