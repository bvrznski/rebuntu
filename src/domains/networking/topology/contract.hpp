#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::networking::topology {
struct TopologyContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
