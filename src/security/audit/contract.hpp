#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::security::audit {
struct AuditContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
