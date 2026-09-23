#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::nftables::chains {
struct ChainsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
