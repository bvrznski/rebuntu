#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::software::repositories {
struct RepositoriesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
