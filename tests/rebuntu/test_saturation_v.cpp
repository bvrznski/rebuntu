#include "domains/common/saturation.hpp"
#include "control/reconciliation/coordination/cross_domain.hpp"
#include <cassert>
#include <iostream>
#include <map>
int main(){
 using namespace rebuntu;using namespace domains::common;
 auto service=DomainReconciler(service_profile(),service_semantics().operations);
 int observations=0, executions=0, checkpoints=0;bool active=false;
 ObserveFn observe=[&](const std::string& id)->std::optional<core::Entity>{++observations;core::Entity e{id,"service",{{"active_state",active?"active":"inactive"},{"load_state","loaded"}},{{"systemd","systemd","observed",std::chrono::system_clock::now()}}};return e;};
 ExecuteFn execute=[&](const core::NativeOperation& op){++executions;if(executions>=2)active=true;return op.provider=="systemd";};
 ReconcileOptions options;options.max_replans=2;options.authorize=[](const core::NativeOperation& op,const security::policy::AuthorizationContext&){return security::policy::AuthorizationResult{security::policy::Decision::allow,"test",security::policy::operation_fingerprint(op)};};options.checkpoint=[&](const core::NativeOperation&,std::size_t){++checkpoints;};
 auto r=service.reconcile({"svc",{{"active_state","active"}},"test"},observe,execute,{},options);
 assert(r.converged&&r.replans==1&&executions==2&&checkpoints==2&&observations>=3);assert(r.journal.committed());
 std::cout<<"REPLAN_CONVERGENCE_PASS\n";
 bool rollback_called=false;int fail_exec=0;auto fail_options=options; auto failing=service.reconcile({"svc",{{"active_state","active"},{"unit_file_state","enabled"}},"failure"},
  [&](const std::string& id)->std::optional<core::Entity>{return core::Entity{id,"service",{{"active_state","inactive"},{"unit_file_state","disabled"},{"load_state","loaded"}}, {}};},
  [&](const core::NativeOperation&){return ++fail_exec==1;},[&](const core::NativeOperation&){rollback_called=true;return true;},fail_options);
 assert(!failing.converged&&failing.rolled_back&&rollback_called&&failing.journal.recovered());
 std::cout<<"TRANSACTION_ROLLBACK_PASS\n";
 using namespace control::reconciliation::coordination;std::vector<std::string> applied;std::vector<std::string> undone;
 auto ok=[&](std::string id){return WorkItem{id,"domain",{},[&,id]{applied.push_back(id);common_result x;x.converged=true;return x;},[&,id]{undone.push_back(id);return true;}};};
 auto a=ok("network");auto b=ok("storage");b.depends_on={"network"};WorkItem c{"service","services",{"storage"},[&]{applied.push_back("service");common_result x;x.errors.push_back("failed");return x;},[]{return true;}};
 auto cross=CrossDomainCoordinator{}.reconcile({c,b,a});assert(!cross.converged&&cross.rolled_back);assert((applied==std::vector<std::string>{"network","storage","service"}));assert((undone==std::vector<std::string>{"storage","network"}));
 std::cout<<"CROSS_DOMAIN_ROLLBACK_PASS\n";
 auto cyc_a=ok("a"),cyc_b=ok("b");cyc_a.depends_on={"b"};cyc_b.depends_on={"a"};auto cyc=CrossDomainCoordinator{}.reconcile({cyc_a,cyc_b});assert(!cyc.converged&&!cyc.errors.empty());
 std::cout<<"CROSS_DOMAIN_CYCLE_PASS\n";
}
