#pragma once
#include <providers/linux/backend.hpp>
#include <control/domain_controller.hpp>
#include <runtime/state/persistence/journal.hpp>
#include <security/policy/policy_engine.hpp>
#include <observation/telemetry/telemetry.hpp>
#include <atomic>
namespace rebuntu::orchestration {
struct ApplyResult{bool accepted{false};bool applied{false};std::string transaction_id,message;};
class ControlRuntime{public:ControlRuntime(management::DomainController&d,model::StateStore&s,policy::PolicyEngine&p,backend::Backend&b,persistence::Journal&j,telemetry::Telemetry&t):domains_(d),state_(s),policy_(p),backend_(b),journal_(j),telemetry_(t){}ApplyResult apply(const management::Request&,bool authorized,bool confirmed);private:management::DomainController&domains_;model::StateStore&state_;policy::PolicyEngine&policy_;backend::Backend&backend_;persistence::Journal&journal_;telemetry::Telemetry&telemetry_;std::atomic_uint64_t sequence_{0};};
}
