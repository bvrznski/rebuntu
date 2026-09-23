#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::automation::retries {
struct RetriesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
