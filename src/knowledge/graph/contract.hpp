#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::knowledge::graph {
struct GraphContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
