#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::pam::session {
struct SessionContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
