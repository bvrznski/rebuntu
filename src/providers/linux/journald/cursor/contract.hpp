#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::journald::cursor {
struct CursorContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
