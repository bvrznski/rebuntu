#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::observation::change_detection {
struct ChangeDetectionContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
