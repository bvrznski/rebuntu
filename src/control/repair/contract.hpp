#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::control::repair {
struct RepairContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
