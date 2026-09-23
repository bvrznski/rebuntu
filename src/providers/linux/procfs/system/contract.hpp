#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::procfs::system {
struct SystemContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
