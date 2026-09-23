#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::governance::migration {
struct MigrationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
