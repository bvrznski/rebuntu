#include "domains/common/saturation.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
using namespace rebuntu::domains::common;
static security::policy::AuthorizeMutation allow_all=[](const core::NativeOperation&,const security::policy::AuthorizationContext& c){return security::policy::AuthorizationResult{security::policy::Decision::allow,"test",c.plan_fingerprint};};
static void verified_case(const DomainSemantics& sem,const char* id,const char* kind,const char* key,const char* before,const char* desired){
 core::Entity state{id,kind,{{key,before}}, {}}; DomainReconciler r(sem.profile,sem.operations); ReconcileOptions o;o.authorize=allow_all;o.authorize_compensation=allow_all;o.max_replans=1;
 auto observe=[&](const std::string&)->std::optional<core::Entity>{return state;};
 auto execute=[&](const core::NativeOperation& op){state.attributes.at(op.arguments.at("attribute"))=op.arguments.at("desired");return true;};
 auto rollback=[](const core::NativeOperation&){return true;};
 auto out=r.reconcile({id,{{key,desired}},"saturation-ix"},observe,execute,rollback,o);assert(out.converged&&out.executed&&out.operation_verifications==1);
}
int main(){
 verified_case(service_semantics(),"svc","service","active_state","inactive","active");
 verified_case(process_semantics(),"proc","process","state","running","stopped");
 verified_case(storage_semantics(),"mnt","storage","mounted","false","true");
 verified_case(networking_semantics(),"eth0","network","link_state","down","up");
 verified_case(software_semantics(),"pkg","package","installed","false","true");
 verified_case(configuration_semantics(),"cfg","configuration","content_state","previous","desired");
 verified_case(accelerator_semantics(),"gpu","accelerator","workload_placement","none","requested");
 std::cout<<"PER_OPERATION_NATIVE_POSTCONDITION_PASS\n";
 {
  auto sem=service_semantics();core::Entity state{"svc","service",{{"active_state","inactive"}}, {}};DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.authorize_compensation=allow_all;o.max_replans=0;int rollbacks=0;
  auto observe=[&](const std::string&)->std::optional<core::Entity>{return state;};auto execute=[](const core::NativeOperation&){return true;};auto rollback=[&](const core::NativeOperation&){++rollbacks;return true;};
  auto out=r.reconcile({"svc",{{"active_state","active"}},"reject false provider success"},observe,execute,rollback,o);assert(!out.converged&&out.rolled_back&&rollbacks==1);assert(!out.errors.empty());
 }
 std::cout<<"FALSE_PROVIDER_SUCCESS_REJECTED_PASS\n";
 {
  auto sem=service_semantics();core::Entity state{"svc","service",{{"active_state","inactive"}}, {}};DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.authorize_compensation=allow_all;o.max_replans=1;int observations=0,executions=0;
  auto observe=[&](const std::string&)->std::optional<core::Entity>{++observations;if(observations==2)state.attributes["external_drift"]="1";return state;};auto execute=[&](const core::NativeOperation& op){++executions;state.attributes[op.arguments.at("attribute")]=op.arguments.at("desired");return true;};
  auto out=r.reconcile({"svc",{{"active_state","active"}},"TOCTOU"},observe,execute,{},o);assert(out.converged&&out.drift_replans==1&&executions==1);
 }
 std::cout<<"PRE_EXECUTION_TOCTOU_REPLAN_PASS\n";
 auto identity=identity_semantics();assert(identity.operations.empty());std::cout<<"IDENTITY_OBSERVATION_ONLY_PASS\n";
}
