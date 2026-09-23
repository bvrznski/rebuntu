#include "domains/common/saturation.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu; using namespace rebuntu::domains::common;
static security::policy::AuthorizeMutation allow_all=[](const core::NativeOperation&,const security::policy::AuthorizationContext& c){return security::policy::AuthorizationResult{security::policy::Decision::allow,"test",c.plan_fingerprint};};
int main(){
 { auto sem=process_semantics();std::optional<core::Entity> state=core::Entity{"p:42","process",{{"state","running"},{"start_ticks","100"}}, {}};DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.native_generation_attribute="start_ticks";o.max_replans=0;
   auto observe=[&](const std::string&){return state;};auto execute=[&](const core::NativeOperation& op){assert(op.verb=="terminate");state.reset();return true;};auto out=r.reconcile({"p:42",{{"state","stopped"}},"terminate"},observe,execute,{},o);assert(out.executed&&out.converged);assert(out.operation_evidence.size()==1&&out.operation_evidence[0].passed&&out.operation_evidence[0].predicate=="entity absent"); }
 std::cout<<"PROCESS_DISAPPEARANCE_POSTCONDITION_PASS\n";
 { auto sem=process_semantics();std::optional<core::Entity> state=core::Entity{"p:42","process",{{"state","running"},{"start_ticks","100"}}, {}};DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.native_generation_attribute="start_ticks";o.max_replans=0;int n=0,exec=0;
   auto observe=[&](const std::string&){++n;if(n==2)state->attributes["start_ticks"]="101";return state;};auto execute=[&](const core::NativeOperation&){++exec;return true;};auto out=r.reconcile({"p:42",{{"state","stopped"}},"pid reuse guard"},observe,execute,{},o);assert(!out.converged&&exec==0&&!out.errors.empty()); }
 std::cout<<"NATIVE_GENERATION_TOKEN_TOCTOU_PASS\n";
 { auto sem=service_semantics();core::Entity state{"svc","service",{{"active_state","inactive"},{"irrelevant","a"}}, {}};DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.native_generation_attribute="generation";o.max_replans=0;int n=0,exec=0;
   auto observe=[&](const std::string&)->std::optional<core::Entity>{++n;if(n==2)state.attributes["irrelevant"]="b";return state;};auto execute=[&](const core::NativeOperation& op){++exec;state.attributes[op.arguments.at("attribute")]=op.arguments.at("desired");return true;};auto out=r.reconcile({"svc",{{"active_state","active"}},"fallback"},observe,execute,{},o);assert(!out.converged&&exec==0); }
 std::cout<<"MISSING_GENERATION_TOKEN_FAIL_CLOSED_PASS\n";
 { auto sem=service_semantics();core::Entity state{"svc","service",{{"active_state","inactive"},{"generation","7"},{"irrelevant","a"}}, {}};DomainReconciler r(sem.profile,sem.operations);ReconcileOptions o;o.authorize=allow_all;o.native_generation_attribute="generation";o.max_replans=0;int n=0;
   auto observe=[&](const std::string&)->std::optional<core::Entity>{++n;if(n==2)state.attributes["irrelevant"]="b";return state;};auto execute=[&](const core::NativeOperation& op){state.attributes[op.arguments.at("attribute")]=op.arguments.at("desired");state.attributes["generation"]="8";return true;};auto out=r.reconcile({"svc",{{"active_state","active"}},"token"},observe,execute,{},o);assert(out.converged&&out.operation_evidence.size()==1);assert(!out.operation_evidence[0].operation_fingerprint.empty()&&out.operation_evidence[0].authority=="systemd"); }
 std::cout<<"OPERATION_BOUND_VERIFICATION_EVIDENCE_PASS\n";
}
