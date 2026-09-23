#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::power::desired_state {
struct DesiredStateContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
