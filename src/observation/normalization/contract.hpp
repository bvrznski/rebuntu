#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::observation::normalization {
struct NormalizationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
