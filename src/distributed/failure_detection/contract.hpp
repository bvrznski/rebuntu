#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::distributed::failure_detection {
struct FailureDetectionContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
