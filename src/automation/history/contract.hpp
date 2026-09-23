#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::automation::history {
struct HistoryContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
