#include "domains/common/saturation.hpp"
#include <cassert>
#include <iostream>
#include <map>
using namespace rebuntu;
using namespace rebuntu::domains::common;
static security::policy::AuthorizeMutation allow_all=[](const core::NativeOperation&,const security::policy::AuthorizationContext& c){return security::policy::AuthorizationResult{security::policy::Decision::allow,"test",c.plan_fingerprint};};
static void compensation_case(const DomainSemantics& sem,const std::string& id,const std::string& kind,const std::string& key,const std::string& before,const std::string& desired,const std::string& expected_inverse){
 core::Entity state{id,kind,{{key,before}}, {}};int forward=0,rollback=0;std::string inverse;
 DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.authorize_compensation=allow_all;o.max_replans=0;
 auto observe=[&](const std::string&)->std::optional<core::Entity>{return state;};
 auto compensate=[&](const core::NativeOperation& op){++rollback;inverse=op.verb;return true;};
 // Force verification failure using a second desired attribute with a supported rule impossible to satisfy is not useful;
 // instead native authority mutates requested key then reports an additional desired key as drift after execution.
 auto bad_execute=[&](const core::NativeOperation&){++forward;state.attributes[key]="authority-refused";return true;};
 auto out=r.reconcile({id,{{key,desired}},"saturation-viii"},observe,bad_execute,compensate,o);
 assert(!out.converged&&out.rolled_back&&rollback==1&&inverse==expected_inverse);
}
int main(){
 compensation_case(service_semantics(),"svc","service","active_state","inactive","active","stop");
 compensation_case(storage_semantics(),"mnt","storage","mounted","false","true","unmount");
 compensation_case(networking_semantics(),"eth0","network","link_state","down","up","down");
 compensation_case(software_semantics(),"pkg","package","installed","false","true","remove");
 compensation_case(configuration_semantics(),"cfg","configuration","content_state","previous","desired","restore");
 std::cout<<"DOMAIN_SPECIFIC_COMPENSATION_PASS\n";
 // Every main domain has deterministic semantics and native authority; identity remains observation-only.
 for(const auto& kind: {"service","process","storage","network","package","configuration","identity","accelerator"}){
  auto s=semantics_for(kind);assert(!s.profile.authority.empty());if(std::string(kind)=="identity")assert(s.operations.empty());
 }
 std::cout<<"EIGHT_DOMAIN_AUTHORITY_BOUNDARY_PASS\n";
 // Internal compensation metadata is deterministic and bound during planning, never guessed during rollback.
 auto sem=service_semantics();auto model=build_model(core::Entity{"svc","service",{{"active_state","inactive"},{"load_state","loaded"}},{}},sem.profile);
 auto plan=OperationPlanner{}.plan({"svc",{{"active_state","active"}},"test"},model,sem.operations);assert(plan.executable()&&plan.plan.operations.size()==1);auto& op=plan.plan.operations.front();assert(op.arguments.at("__compensation_verb")=="stop"&&op.arguments.at("__compensation_provider")=="systemd");
 std::cout<<"PLANNED_COMPENSATION_BINDING_PASS\n";
}
