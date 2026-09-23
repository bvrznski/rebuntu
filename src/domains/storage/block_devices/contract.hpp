#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::storage::block_devices {
struct BlockDevicesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
