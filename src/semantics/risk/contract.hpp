#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::risk {
struct RiskContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
