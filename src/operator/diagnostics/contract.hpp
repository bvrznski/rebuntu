#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::diagnostics {
struct DiagnosticsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
