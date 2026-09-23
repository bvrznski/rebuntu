#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::cgroups::hierarchy {
struct HierarchyContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
