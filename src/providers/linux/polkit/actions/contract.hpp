#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::polkit::actions {
struct ActionsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
