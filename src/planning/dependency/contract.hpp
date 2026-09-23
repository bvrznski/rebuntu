#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::planning::dependency {
struct DependencyContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
