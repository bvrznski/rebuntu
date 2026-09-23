#pragma once
#include "../operations/planner.hpp"
#include "../profiles.hpp"
#include "../health/evaluator.hpp"
#include "../../../core/transactions/journal.hpp"
#include "../../../security/policy/mutation_gate.hpp"
#include <functional>
#include <map>
#include <sstream>
#include <charconv>
namespace rebuntu::domains::common {
using ObserveFn=std::function<std::optional<core::Entity>(const std::string&)>; using ExecuteFn=std::function<bool(const core::NativeOperation&)>;
using CheckpointFn=std::function<void(const core::NativeOperation&,std::size_t)>;
using ObserveRelationshipsFn=std::function<std::vector<Relationship>(const std::string&)>;
struct ReconcileOptions {
 bool apply{true}; std::size_t max_replans{1}; std::size_t max_operations{64}; std::size_t max_stagnant_replans{1}; bool reject_repeated_state{true}; bool guard_pre_execution_drift{true}; bool guard_each_operation_drift{true}; bool verify_each_operation{true}; CheckpointFn checkpoint{};
 security::policy::AuthorizeMutation authorize{}; security::policy::AuthorizeMutation authorize_compensation{};
 security::policy::AuthorizationContext authorization_context{};
 ObserveRelationshipsFn observe_relationships{}; std::string transaction_binding{};
 // Optional native generation/version attribute supplied by a provider (for example procfs start_ticks, systemd invocation id, link generation).
 // When present, only this authority token participates in the pre-execution concurrency guard; it is never synthesized by Rebuntu.
 std::string native_generation_attribute{};
};
struct OperationVerificationEvidence { std::string operation_fingerprint; std::string authority; std::string predicate; std::string observed; std::string transaction_binding; std::size_t operation_index{0}; bool passed{false}; };
struct ReconcileResult { bool converged{false}; bool executed{false}; bool rolled_back{false}; std::size_t replans{0}; std::size_t operation_verifications{0}; std::size_t drift_replans{0}; core::Plan plan; core::Verification verification; std::vector<OperationVerificationEvidence> operation_evidence; core::transactions::Journal journal; std::vector<std::string> errors; };
class DomainReconciler {
 DomainProfile profile_; std::vector<OperationRuleV2> rules_;
 static std::string state_fingerprint(const core::Entity& e){std::ostringstream os;os<<e.id<<'\n'<<e.kind<<'\n';for(const auto& [k,v]:e.attributes)os<<k.size()<<':'<<k<<'='<<v.size()<<':'<<v<<'\n';return os.str();}
 static std::optional<std::string> generation_token(const core::Entity& e,const ReconcileOptions& options){ if(options.native_generation_attribute.empty())return std::nullopt;auto i=e.attributes.find(options.native_generation_attribute);if(i==e.attributes.end())return std::nullopt;return i->second; }
 static bool same_concurrency_version(const core::Entity& before,const core::Entity& guard,const ReconcileOptions& options){auto a=generation_token(before,options),b=generation_token(guard,options);if(a||b)return a&&b&&*a==*b;return state_fingerprint(before)==state_fingerprint(guard);}
 static bool numeric(const std::string& s,double& value){try{std::size_t n=0;value=std::stod(s,&n);return n==s.size();}catch(...){return false;}}
 static bool verify_operation(const core::NativeOperation& op,const std::optional<core::Entity>& observed,const DomainProfile& profile,ReconcileResult& out,std::size_t operation_index,const ReconcileOptions& options){
  ++out.operation_verifications;const auto fp=security::policy::operation_fingerprint(op);auto mode=op.arguments.find("__verify_mode");const std::string verify_mode=mode==op.arguments.end()?"equals":mode->second;OperationVerificationEvidence ev;ev.operation_fingerprint=fp;ev.authority=profile.authority;ev.operation_index=operation_index;ev.transaction_binding=options.transaction_binding;
  if(verify_mode=="absent"||verify_mode=="absent_or_equals"){if(!observed){ev.predicate="entity absent";ev.observed="absent";ev.passed=true;out.operation_evidence.push_back(ev);return true;}if(verify_mode=="absent"){ev.predicate="entity absent";ev.observed="present";ev.passed=false;out.operation_evidence.push_back(ev);return false;}}
  if(verify_mode=="present"){ev.predicate="entity present";ev.observed=observed?"present":"absent";ev.passed=observed.has_value();out.operation_evidence.push_back(ev);return ev.passed;}
  auto attribute=op.arguments.find("attribute"),expected=op.arguments.find("desired");if(!observed){ev.predicate="authoritative entity available";ev.observed="absent";ev.passed=false;out.operation_evidence.push_back(ev);return false;}
  bool rich=false,rich_ok=true;
  for(const auto& [k,v]:op.arguments){
   const std::string eq="__verify_equals.",mn="__verify_min.",mx="__verify_max.";std::string attr;enum class P{eq,min,max} pred;
   if(k.rfind(eq,0)==0){attr=k.substr(eq.size());pred=P::eq;}else if(k.rfind(mn,0)==0){attr=k.substr(mn.size());pred=P::min;}else if(k.rfind(mx,0)==0){attr=k.substr(mx.size());pred=P::max;}else continue;rich=true;
   OperationVerificationEvidence pev;pev.operation_fingerprint=fp;pev.authority=profile.authority;pev.operation_index=operation_index;pev.transaction_binding=options.transaction_binding;auto ai=observed->attributes.find(attr);pev.observed=ai==observed->attributes.end()?"<missing>":ai->second;
   if(pred==P::eq){pev.predicate=attr+"="+v;pev.passed=ai!=observed->attributes.end()&&ai->second==v;}else{double av=0,bv=0;const bool nums=ai!=observed->attributes.end()&&numeric(ai->second,av)&&numeric(v,bv);pev.predicate=attr+(pred==P::min?">=":"<=")+v;pev.passed=nums&&(pred==P::min?av>=bv:av<=bv);}
   rich_ok=rich_ok&&pev.passed;out.operation_evidence.push_back(pev);
  }
  bool relationship_rich=false,relationship_ok=true;
  for(const auto& [k,v]:op.arguments){
   const std::string prefix="__verify_relationship.";if(k.rfind(prefix,0)!=0)continue;relationship_rich=true;OperationVerificationEvidence rev;rev.operation_fingerprint=fp;rev.authority=profile.authority;rev.operation_index=operation_index;rev.transaction_binding=options.transaction_binding;const auto predicate=k.substr(prefix.size());rev.predicate="relationship "+predicate+"->"+v;
   if(!options.observe_relationships){rev.observed="<relationship observation unavailable>";rev.passed=false;}else{auto rels=options.observe_relationships(op.target);auto it=std::find_if(rels.begin(),rels.end(),[&](const Relationship& r){return r.subject==op.target&&r.predicate==predicate&&r.object==v;});rev.passed=it!=rels.end();rev.observed=rev.passed?v:"<missing>";}relationship_ok=relationship_ok&&rev.passed;out.operation_evidence.push_back(rev);
  }
  if(rich||relationship_rich)return rich_ok&&relationship_ok;
  if(attribute==op.arguments.end()||expected==op.arguments.end()){ev.predicate="provider success plus entity present";ev.observed="present";ev.passed=true;out.operation_evidence.push_back(ev);return true;}
  ev.predicate=attribute->second+"="+expected->second;auto actual=observed->attributes.find(attribute->second);ev.observed=actual==observed->attributes.end()?"<missing>":actual->second;ev.passed=actual!=observed->attributes.end()&&actual->second==expected->second;out.operation_evidence.push_back(ev);return ev.passed;
 }
 static void rollback_applied(std::vector<core::NativeOperation>& applied,const ExecuteFn& rollback,ReconcileResult& out,const ReconcileOptions& options){
  if(!rollback||applied.empty()){return;} out.journal.advance(core::transactions::Stage::rolling_back,"rollback requested"); bool ok=true;
  for(auto i=applied.rbegin();i!=applied.rend();++i){auto inv=*i;auto p=inv.arguments.find("previous");auto cv=inv.arguments.find("__compensation_verb");if(p==inv.arguments.end()&&cv==inv.arguments.end())continue;if(p!=inv.arguments.end())inv.arguments["desired"]=p->second;if(cv!=inv.arguments.end())inv.verb=cv->second;auto cp=inv.arguments.find("__compensation_provider");if(cp!=inv.arguments.end())inv.provider=cp->second;inv.arguments.erase("__compensation_verb");inv.arguments.erase("__compensation_provider");
   if(inv.mutating){auto auth=options.authorize_compensation?options.authorize_compensation:options.authorize;if(auth){auto ctx=options.authorization_context;ctx.compensation=true;ctx.plan_fingerprint=security::policy::operation_fingerprint(inv);auto decision=auth(inv,ctx);if(!decision.allowed_for(ctx.plan_fingerprint)){ok=false;out.errors.push_back("rollback authorization denied: "+inv.verb);continue;}}}
   if(!rollback(inv)){ok=false;out.errors.push_back("rollback failed: "+inv.verb);}}
  out.rolled_back=true;out.journal.advance(ok?core::transactions::Stage::rolled_back:core::transactions::Stage::failed,ok?"rollback converged":"rollback incomplete");
 }
public:
 DomainReconciler(DomainProfile p,std::vector<OperationRuleV2> r):profile_(std::move(p)),rules_(std::move(r)){}
 ReconcileResult reconcile(const DesiredResourceState& desired,const ObserveFn& observe,const ExecuteFn& execute,const ExecuteFn& rollback={},bool apply=true) const {ReconcileOptions o;o.apply=apply;return reconcile(desired,observe,execute,rollback,o);}
 ReconcileResult reconcile(const DesiredResourceState& desired,const ObserveFn& observe,const ExecuteFn& execute,const ExecuteFn& rollback,const ReconcileOptions& options) const {
  ReconcileResult out;std::vector<core::NativeOperation> applied;std::map<std::string,std::size_t> observed_states;std::size_t operations_executed=0;
  for(std::size_t attempt=0;;++attempt){
   auto before=observe(desired.stable_id);if(!before){out.errors.push_back("authoritative observation unavailable");out.journal.advance(core::transactions::Stage::failed,"initial observation unavailable");return out;}
   auto before_fp=state_fingerprint(*before);auto& seen=observed_states[before_fp];if(options.reject_repeated_state&&seen++>options.max_stagnant_replans){out.errors.push_back("reconciliation made no observable progress");rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"repeated authoritative state");return out;}
   auto model=build_model(*before,profile_);auto planned=OperationPlanner{}.plan(desired,model,rules_);out.plan=planned.plan;
   if(!planned.executable()){out.errors=planned.blocked;out.journal.advance(core::transactions::Stage::failed,"planning blocked");return out;}
   if(!options.apply){out.verification=verify(desired,model.resource);out.converged=out.verification.converged;out.journal.advance(out.converged?core::transactions::Stage::committed:core::transactions::Stage::failed,"dry-run verification");return out;}
   if(out.plan.operations.empty()){out.verification=verify(desired,model.resource);out.converged=out.verification.converged;out.journal.advance(out.converged?core::transactions::Stage::committed:core::transactions::Stage::failed,"already converged");return out;}
   if(options.guard_pre_execution_drift){auto guard=observe(desired.stable_id);if(!guard){out.errors.push_back("pre-execution authoritative observation unavailable");out.journal.advance(core::transactions::Stage::failed,"pre-execution observation unavailable");return out;}if(!same_concurrency_version(*before,*guard,options)){if(attempt>=options.max_replans){out.errors.push_back("authoritative state changed between planning and execution");out.journal.advance(core::transactions::Stage::failed,"pre-execution drift exhausted replan budget");return out;}++out.replans;++out.drift_replans;out.journal.advance(core::transactions::Stage::replanning,"TOCTOU guard observed drift before mutation");continue;}}
   if(attempt==0)out.journal.advance(core::transactions::Stage::executing,"executing native plan");else out.journal.advance(core::transactions::Stage::executing,"executing replanned native plan");
   bool operation_verification_failed=false;std::optional<core::Entity> operation_baseline=before;std::size_t operation_index=0;
   for(const auto& op:out.plan.operations){
    if(++operations_executed>options.max_operations){out.errors.push_back("operation budget exhausted");rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"operation budget exhausted");return out;}
    if(options.guard_each_operation_drift&&operation_baseline){auto cas=observe(desired.stable_id);if(!cas||!same_concurrency_version(*operation_baseline,*cas,options)){out.errors.push_back("authoritative state changed before operation CAS");rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"per-operation stale-plan rejection");return out;}operation_baseline=cas;}
    if(op.mutating){if(!options.authorize){out.errors.push_back("authorization unavailable for mutating operation: "+op.verb);rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"authorization unavailable");return out;}auto ctx=options.authorization_context;ctx.attempt=attempt;ctx.plan_fingerprint=security::policy::operation_fingerprint(op);auto decision=options.authorize(op,ctx);if(!decision.allowed_for(ctx.plan_fingerprint)){out.errors.push_back("authorization denied: "+op.verb+(decision.reason.empty()?std::string{}:": "+decision.reason));rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"authorization denied");return out;}}
    if(options.checkpoint){options.checkpoint(op,applied.size());}
    if(!execute(op)){out.errors.push_back("native operation failed: "+op.verb);rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"execution failed");return out;}applied.push_back(op);out.executed=true;
    if(options.verify_each_operation){auto observed=observe(desired.stable_id);if(!verify_operation(op,observed,profile_,out,operation_index,options)){auto mode=op.arguments.find("__verify_mode");if(mode!=op.arguments.end()&&mode->second=="absent")out.errors.push_back("native postcondition failed: "+op.verb+" did not remove entity from authoritative observation");else out.errors.push_back("native postcondition failed: "+op.verb+" did not establish its authoritative predicate");operation_verification_failed=true;break;}operation_baseline=observed;}++operation_index;}
   if(operation_verification_failed){rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"operation postcondition verification failed");return out;}
   out.journal.advance(core::transactions::Stage::verifying,"authoritative re-observation");auto after=observe(desired.stable_id);if(!after){bool absence_expected=!applied.empty()&&applied.back().arguments.count("__verify_mode")&&(applied.back().arguments.at("__verify_mode")=="absent"||applied.back().arguments.at("__verify_mode")=="absent_or_equals");if(absence_expected){out.verification.converged=true;out.converged=true;out.journal.advance(core::transactions::Stage::committed,"verified authoritative disappearance");return out;}out.errors.push_back("post-operation observation unavailable");rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"verification observation unavailable");return out;}
   out.verification=verify(desired,build_model(*after,profile_).resource);out.converged=out.verification.converged;if(out.converged){out.journal.advance(core::transactions::Stage::committed,"verified convergence");return out;}
   if(attempt>=options.max_replans){out.errors.push_back("verification did not converge");rollback_applied(applied,rollback,out,options);if(!out.rolled_back)out.journal.advance(core::transactions::Stage::failed,"replan budget exhausted");return out;}
   ++out.replans;out.journal.advance(core::transactions::Stage::replanning,"authoritative state drift; replanning");
  }
 }
};
}
