#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::filesystems::mount {
struct MountContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
