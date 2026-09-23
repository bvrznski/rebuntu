#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::natural_language {
struct NaturalLanguageContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
