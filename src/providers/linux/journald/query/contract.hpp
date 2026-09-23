#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::journald::query {
struct QueryContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
