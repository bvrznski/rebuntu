#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::governance::architecture_audit {
struct ArchitectureAuditContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
