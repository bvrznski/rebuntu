#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::lifecycle {
struct LifecycleContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
