#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::workloads::limits {
struct LimitsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
