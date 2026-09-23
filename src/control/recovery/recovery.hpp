#pragma once
#include <providers/linux/backend.hpp>
#include <runtime/state/persistence/journal.hpp>
#include <observation/telemetry/telemetry.hpp>
#include <string>
namespace rebuntu::recovery {
struct RecoveryResult{bool recovered{false};std::string message;};
class RecoveryCoordinator{public:RecoveryCoordinator(persistence::Journal&j,backend::Backend&b,telemetry::Telemetry&t):journal_(j),backend_(b),telemetry_(t){}RecoveryResult rollback_target(const std::string& target);private:persistence::Journal&journal_;backend::Backend&backend_;telemetry::Telemetry&telemetry_;};
}
