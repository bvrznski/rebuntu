#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::workloads::priorities {
struct PrioritiesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
