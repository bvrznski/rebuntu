#include "../../src/domains/common/capabilities/resolver.hpp"
#include "../../src/domains/common/desired_state/differ.hpp"
#include "../../src/domains/common/topology/analyzer.hpp"
#include "../../src/domains/common/health/evaluator.hpp"
#include "../../src/domains/common/operations/planner.hpp"
#include "../../src/domains/common/reconciliation/domain_reconciler.hpp"
#include "../../src/domains/common/saturation.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
int main(){
 core::Entity svc{"systemd:sshd.service","service",{{"active_state","inactive"},{"unit_file_state","disabled"}},{{"systemd","systemd","inactive",{}}}};
 auto sem=domains::common::service_semantics(); auto model=domains::common::build_model(svc,sem.profile);
 assert(domains::common::CapabilityResolver{}.resolve(model,{"start",{}}).allowed); std::cout<<"CAPABILITY_RESOLVER_PASS\n";
 domains::common::DesiredResourceState want{svc.id,{{"active_state","active"},{"unit_file_state","enabled"}},"test"};
 assert(domains::common::DesiredStateDiffer{}.diff(want,model.resource).changes.size()==2); std::cout<<"DESIRED_STATE_DIFF_PASS\n";
 domains::common::Topology t; t.add({{"disk","storage","sysfs","disk"},{},{}});t.add({{"mount","storage","procfs","mount"},{},{}});assert(t.link({"mount","depends_on","disk",{}}));auto ta=domains::common::TopologyAnalyzer{}.analyze(t);assert(ta.acyclic&&ta.order.front()=="disk");std::cout<<"TOPOLOGY_ANALYZER_PASS\n";
 domains::common::Health h{{{"carrier","degraded","no carrier",{"netlink","kernel","down",{}}}}};assert(domains::common::HealthEvaluator{}.evaluate(h).state==domains::common::HealthState::degraded);std::cout<<"HEALTH_EVALUATOR_PASS\n";
 auto pr=domains::common::OperationPlanner{}.plan(want,model,sem.operations);assert(pr.executable()&&pr.plan.operations.size()==2&&pr.plan.operations[0].provider=="systemd");std::cout<<"OPERATION_PLANNER_PASS\n";
 core::Entity state=svc; domains::common::DomainReconciler rec{sem.profile,sem.operations};
 auto observe=[&](const std::string&)->std::optional<core::Entity>{return state;}; auto exec=[&](const core::NativeOperation& op){if(op.verb=="start")state.attributes["active_state"]="active";else if(op.verb=="enable")state.attributes["unit_file_state"]="enabled";else return false;return true;};
 domains::common::ReconcileOptions authorized; authorized.authorize=[](const core::NativeOperation& op,const security::policy::AuthorizationContext& c){return security::policy::AuthorizationResult{security::policy::Decision::allow,"test",c.plan_fingerprint.empty()?security::policy::operation_fingerprint(op):c.plan_fingerprint};};
 auto rr=rec.reconcile(want,observe,exec,{},authorized);assert(rr.converged&&rr.executed);std::cout<<"DOMAIN_RECONCILER_PASS\n";
 const char* kinds[]={"service","process","storage","network","package","configuration","identity","accelerator"};for(auto k:kinds){auto s=domains::common::semantics_for(k);assert(!s.profile.authority.empty());}std::cout<<"DOMAIN_SATURATION_8_PASS\n";
 domains::common::Topology cyc;cyc.add({{"a","x","n","a"},{},{}});cyc.add({{"b","x","n","b"},{},{}});cyc.link({"a","depends_on","b",{}});cyc.link({"b","depends_on","a",{}});assert(!domains::common::TopologyAnalyzer{}.analyze(cyc).acyclic);std::cout<<"DEPENDENCY_CYCLE_PASS\n";
 core::Entity bad=svc;int calls=0;auto fail=[&](const core::NativeOperation&){return ++calls<2;};int rollbacks=0;auto rb=[&](const core::NativeOperation&){++rollbacks;return true;};auto r2=rec.reconcile(want,[&](const std::string&)->std::optional<core::Entity>{return bad;},fail,rb,authorized);assert(!r2.converged&&r2.rolled_back&&rollbacks==1);std::cout<<"ROLLBACK_PATH_PASS\n";
}
