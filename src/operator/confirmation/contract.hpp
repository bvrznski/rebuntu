#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::operator_ui::confirmation {
struct ConfirmationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
