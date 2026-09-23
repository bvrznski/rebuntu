#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::history {
struct HistoryContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
