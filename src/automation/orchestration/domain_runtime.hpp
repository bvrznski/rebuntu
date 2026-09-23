#pragma once
#include <providers/linux/backend.hpp>
#include <domains/linux_domains.hpp>
#include <semantics/entities/state_store.hpp>
#include <runtime/state/persistence/journal.hpp>
#include <security/policy/policy_engine.hpp>
#include <observation/telemetry/telemetry.hpp>
namespace rebuntu::orchestration {
struct DomainApplyResult { bool accepted{false}, executed{false}, verified{false}; std::string transaction_id,message; };
class DomainRuntime {
public:
 DomainRuntime(model::StateStore&s,policy::PolicyEngine&p,backend::Backend&b,persistence::Journal&j,telemetry::Telemetry&t,const domains::LinuxDomainRegistry&r):state_(s),policy_(p),backend_(b),journal_(j),telemetry_(t),registry_(r){}
 DomainApplyResult apply(const management::Request&,bool authorized,bool confirmed);
 std::map<std::string,backend::Result> inspect(management::Domain,const std::string& target);
private:model::StateStore&state_;policy::PolicyEngine&policy_;backend::Backend&backend_;persistence::Journal&journal_;telemetry::Telemetry&telemetry_;const domains::LinuxDomainRegistry&registry_;uint64_t seq_{0};
};
}
