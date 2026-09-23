#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::confidence {
struct ConfidenceContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
