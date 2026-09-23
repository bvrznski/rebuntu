#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::state {
struct StateContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
