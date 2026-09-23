#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::context {
struct ContextContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
