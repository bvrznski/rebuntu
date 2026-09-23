#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::events {
struct EventsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
