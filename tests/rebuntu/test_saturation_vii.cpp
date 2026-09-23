#include "domains/common/saturation.hpp"
#include "control/checkpoints/durable_store.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
using namespace rebuntu;
int main(){
 using namespace domains::common;
 auto service=DomainReconciler(service_profile(),service_semantics().operations);
 security::policy::AuthorizeMutation allow=[](const core::NativeOperation&,const security::policy::AuthorizationContext& c){return security::policy::AuthorizationResult{security::policy::Decision::allow,"ok",c.plan_fingerprint};};
 // Native authority accepts the call but reports exactly the same state: stop instead of thrashing/retrying forever.
 int calls=0; ReconcileOptions stagnant;stagnant.max_replans=8;stagnant.max_stagnant_replans=0;stagnant.authorize=allow;
 ObserveFn unchanged=[](const std::string& id)->std::optional<core::Entity>{return core::Entity{id,"service",{{"active_state","inactive"},{"load_state","loaded"}}, {}};};
 auto no_progress=service.reconcile({"svc",{{"active_state","active"}},"test"},unchanged,[&](const core::NativeOperation&){++calls;return true;},{},stagnant);
 assert(!no_progress.converged&&calls==1&&!no_progress.errors.empty()&&(no_progress.errors.back()=="reconciliation made no observable progress"||no_progress.errors.back().find("native postcondition failed:")==0));
 std::cout<<"ANTI_THRASH_NO_PROGRESS_PASS\n";
 // Operation budget is independent of replan budget and fails closed before an unbounded mutation sequence.
 ReconcileOptions budget;budget.max_replans=8;budget.max_operations=0;budget.authorize=allow;calls=0;
 auto bounded=service.reconcile({"svc",{{"active_state","active"}},"test"},unchanged,[&](const core::NativeOperation&){++calls;return true;},{},budget);
 assert(!bounded.converged&&calls==0&&bounded.errors.back()=="operation budget exhausted");
 std::cout<<"OPERATION_BUDGET_PASS\n";
 // Durable store rejects malformed persisted state instead of silently recovering fabricated truth.
 namespace fs=std::filesystem;auto path=fs::temp_directory_path()/"rebuntu-saturation-vii.journal";fs::remove(path);
 control::checkpoints::DurableStore store(path);store.append({"tx","work",control::checkpoints::DurableStage::prepared,0});
 {std::ofstream out(path,std::ios::app);out<<"corrupt-line\n";}
 bool rejected=false;try{(void)store.load();}catch(const std::runtime_error&){rejected=true;}assert(rejected);fs::remove(path);
 std::cout<<"DURABLE_CORRUPTION_FAIL_CLOSED_PASS\n";
}
