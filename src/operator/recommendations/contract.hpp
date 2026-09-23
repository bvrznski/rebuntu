#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::recommendations {
struct RecommendationsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
