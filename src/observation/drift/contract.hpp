#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::observation::drift {
struct DriftContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
