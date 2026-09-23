#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::observation::inventory {
struct InventoryContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
