#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::knowledge::facts {
struct FactsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
