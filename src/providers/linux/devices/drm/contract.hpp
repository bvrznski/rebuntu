#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::devices::drm {
struct DrmContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
