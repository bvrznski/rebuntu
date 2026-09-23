#include <runtime/production.hpp>
#include <cassert>
using namespace rebuntu;
int main(){
 using namespace runtime::production;
 Initializer init; RuntimeContext c; c.runtime_id="test"; auto ir=init.initialize(c,{{"config",{},true,true},{"providers",{"config"},true,true}}); assert(ir.outcome.is_success());
 assert(!Initializer::startup_order({{"a",{"b"}},{"b",{"a"}}}));
 infrastructure::ProviderSelectionRegistry pr; assert(pr.register_provider({"native",infrastructure::ProviderType::kRuntime,{"test.op"},10,true,true,"inline"})); assert(!pr.register_provider({"native"}));
 Resolver r; core::OperationDefinition op; op.id="test.op";op.provider_ids={"native"}; assert(r.add_operation(op)); r.set_provider_registry(&pr);
 Dispatcher d; assert(d.register_handler("test.op",[](const auto&,const auto&,auto&t){return t.is_cancelled()?core::Outcome::cancelled("cancelled"):core::Outcome::completed();})); assert(!d.register_handler("test.op",{}));
 Engine e(ir.context,r,d); core::OperationRequest req;req.operation_id="test.op"; auto out=e.submit(req); assert(out.status==core::SemanticStatus::kCompleted);
 OperationHooks hooks; hooks.authorize=[](const auto&){return core::Outcome::success(true);};hooks.verify=[](const auto&){return core::Outcome::success(true);};out=e.submit(req,hooks);assert(out.is_success());
 JobRecord jr; jr.job.id=runtime::work::JobId{"j"};jr.job.max_attempts=runtime::work::AttemptNumber{3};int n=0;CancellationToken tok;out=JobRuntime{}.run(jr,[&](int){++n;return n<2?core::Outcome::failure("E","x"):core::Outcome::success(true);},tok);assert(out.is_success()&&jr.attempts.size()==2);
 runtime::Event ev;ev.id="evt";ActivationGate ag;assert(ag.activate(ev,"t",req));assert(!ag.activate(ev,"t",req));
 Coordinator co;assert(co.acquire("r","a"));assert(!co.acquire("r","b"));co.release("r","a");assert(co.acquire("r","b"));
 auto child=std::make_shared<CancellationToken>();ShutdownCoordinator sh;assert(sh.shutdown(e,{child},std::chrono::milliseconds(0)).is_success());assert(child->is_cancelled());assert(e.context().lifecycle==runtime::LifecycleState::kStopped);
 return 0;
}
