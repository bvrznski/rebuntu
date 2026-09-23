#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::portability::platform_detection {
struct PlatformDetectionContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
