#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::knowledge::system_model {
struct SystemModelContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
