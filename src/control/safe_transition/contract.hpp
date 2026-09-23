#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::control::safe_transition {
struct SafeTransitionContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
