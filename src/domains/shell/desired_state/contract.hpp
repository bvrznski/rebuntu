#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::shell::desired_state {
struct DesiredStateContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
