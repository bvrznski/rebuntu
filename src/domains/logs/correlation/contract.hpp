#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::logs::correlation {
struct CorrelationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
