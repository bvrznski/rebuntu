#include "domains/common/saturation.hpp"
#include "control/reconciliation/coordination/durable_cross_domain.hpp"
#include "security/policy/mutation_gate.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
int main(){
 using namespace rebuntu;using namespace domains::common;
 auto service=DomainReconciler(service_profile(),service_semantics().operations);bool active=false;int executed=0,auth_calls=0;
 ObserveFn observe=[&](const std::string& id)->std::optional<core::Entity>{return core::Entity{id,"service",{{"active_state",active?"active":"inactive"},{"load_state","loaded"}}, {}};};
 ReconcileOptions denied;denied.authorize=[&](const core::NativeOperation&,const security::policy::AuthorizationContext&){++auth_calls;return security::policy::AuthorizationResult{security::policy::Decision::deny,"policy",{}};};
 auto no=service.reconcile({"svc",{{"active_state","active"}},"test"},observe,[&](const core::NativeOperation&){++executed;active=true;return true;},{},denied);assert(!no.converged&&executed==0&&auth_calls==1);std::cout<<"MUTATION_FAIL_CLOSED_PASS\n";
 ReconcileOptions allowed;allowed.authorize=[&](const core::NativeOperation& op,const security::policy::AuthorizationContext& ctx){++auth_calls;assert(ctx.plan_fingerprint==security::policy::operation_fingerprint(op));return security::policy::AuthorizationResult{security::policy::Decision::allow,"ok",ctx.plan_fingerprint};};
 auto yes=service.reconcile({"svc",{{"active_state","active"}},"test"},observe,[&](const core::NativeOperation&){++executed;active=true;return true;},{},allowed);assert(yes.converged&&executed==1);std::cout<<"AUTHORIZED_MUTATION_PASS\n";
 active=false;ReconcileOptions stale;stale.authorize=[](const core::NativeOperation&,const security::policy::AuthorizationContext&){return security::policy::AuthorizationResult{security::policy::Decision::allow,"stale","wrong-plan"};};auto toctou=service.reconcile({"svc",{{"active_state","active"}},"test"},observe,[&](const core::NativeOperation&){++executed;return true;},{},stale);assert(!toctou.converged&&executed==1);std::cout<<"AUTHORIZATION_BINDING_PASS\n";
 namespace fs=std::filesystem;auto path=fs::temp_directory_path()/"rebuntu-saturation-vi.journal";fs::remove(path);control::checkpoints::DurableStore store(path);using namespace control::reconciliation::coordination;std::vector<std::string> calls;
 WorkItem a{"network","networking",{},[&]{calls.push_back("network");common_result r;r.converged=true;return r;},[&]{calls.push_back("undo-network");return true;}};
 WorkItem b{"service","services",{"network"},[&]{calls.push_back("service");common_result r;r.converged=true;return r;},[&]{calls.push_back("undo-service");return true;}};
 // Simulate a crash after the first domain was durably applied.
 store.append({"tx1","network",control::checkpoints::DurableStage::prepared,0});store.append({"tx1","network",control::checkpoints::DurableStage::applied,1});
 auto resumed=DurableCrossDomainCoordinator(store).reconcile("tx1",{b,a});assert(resumed.resumed&&resumed.reconciliation.converged);assert((calls==std::vector<std::string>{"service"}));assert(resumed.recovered_work.size()==1&&resumed.recovered_work[0]=="network");auto records=store.transaction("tx1");assert(!records.empty()&&records.back().stage==control::checkpoints::DurableStage::committed);std::cout<<"CRASH_RESUME_CHECKPOINT_PASS\n";
 calls.clear();store.append({"tx2","network",control::checkpoints::DurableStage::applied,0});WorkItem fail{"service","services",{"network"},[&]{calls.push_back("fail-service");common_result r;r.errors.push_back("boom");return r;},[&]{return true;}};auto recovered_failure=DurableCrossDomainCoordinator(store).reconcile("tx2",{fail,a});assert(!recovered_failure.reconciliation.converged&&recovered_failure.reconciliation.rolled_back);assert((calls==std::vector<std::string>{"fail-service","undo-network"}));std::cout<<"RESUMED_TRANSACTION_ROLLBACK_PASS\n";
 fs::remove(path);
}
