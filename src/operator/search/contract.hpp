#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::search {
struct SearchContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
