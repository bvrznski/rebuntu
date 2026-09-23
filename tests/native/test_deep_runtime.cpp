#include <providers/linux/backend.hpp>
#include <control/domain_controller.hpp>
#include <semantics/entities/state_store.hpp>
#include <automation/orchestration/control_runtime.hpp>
#include <runtime/state/persistence/journal.hpp>
#include <security/policy/policy_engine.hpp>
#include <control/recovery/recovery.hpp>
#include <observation/telemetry/telemetry.hpp>
#include <cassert>
#include <filesystem>
#include <iostream>
int main(){
 using namespace rebuntu;
 auto path=std::filesystem::temp_directory_path()/"rebuntu-deep-runtime.journal"; std::filesystem::remove(path);
 model::StateStore state; state.upsert({"sshd","enabled","false","test",1.0});
 management::DomainController domains(state); policy::PolicyEngine policy; backend::DryRunBackend backend; persistence::Journal journal(path); telemetry::Telemetry telemetry;
 orchestration::ControlRuntime runtime(domains,state,policy,backend,journal,telemetry);
 management::Request request{management::Domain::service,"sshd","enabled","true"};
 auto denied=runtime.apply(request,false,true); assert(!denied.applied);
 auto applied=runtime.apply(request,true,true); assert(applied.accepted&&applied.applied); assert(state.get("sshd","enabled")->value=="true"); assert(journal.latest("sshd").has_value()); assert(telemetry.counter("control","apply").attempts==2); assert(backend.commands().size()==1);
 recovery::RecoveryCoordinator recovery(journal,backend,telemetry); auto rr=recovery.rollback_target("sshd"); assert(rr.recovered); assert(backend.commands().size()==2); assert(telemetry.counter("recovery","rollback").successes==1);
 std::filesystem::remove(path); std::cout<<"deep runtime ok\n";
}
