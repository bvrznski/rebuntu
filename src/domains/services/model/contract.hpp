#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::services::model {
struct ModelContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
