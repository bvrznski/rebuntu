#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::planning::preconditions {
struct PreconditionsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
