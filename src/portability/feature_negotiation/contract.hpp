#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::portability::feature_negotiation {
struct FeatureNegotiationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
