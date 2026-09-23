#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::knowledge::history {
struct HistoryContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
