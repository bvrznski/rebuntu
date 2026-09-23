#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::nftables::tables {
struct TablesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
