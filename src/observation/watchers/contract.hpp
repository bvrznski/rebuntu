#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::observation::watchers {
struct WatchersContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
