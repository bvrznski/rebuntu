#pragma once
#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>
#include <runtime/work.hpp>
#include <runtime/workflow.hpp>
#include <domains/development/infrastructure/selection.hpp>
#include <atomic>
#include <chrono>
#include <functional>
#include <map>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::runtime::production {
struct CancellationToken { std::atomic_bool cancelled{false}; void cancel(){cancelled.store(true);} bool is_cancelled()const{return cancelled.load();} };
struct RuntimeContext { std::string runtime_id; std::string scope="user"; std::string state_root; std::string evidence_root; LifecycleState lifecycle=LifecycleState::kCreated; ReadinessState readiness=ReadinessState::kNotReady; std::shared_ptr<CancellationToken> cancellation=std::make_shared<CancellationToken>(); std::vector<core::Evidence> evidence; };
struct Dependency { std::string id; std::vector<std::string> dependencies; bool required=true; bool ready=true; };
struct InitResult { core::Outcome outcome; RuntimeContext context; std::optional<std::string> failed_stage; };
class Initializer { public: InitResult initialize(RuntimeContext c, const std::vector<Dependency>& deps) const; static std::optional<std::vector<std::string>> startup_order(const std::vector<Dependency>& deps); };
struct ResolvedWork { core::OperationDefinition operation; std::string provider_id; work::ExecutionMode mode=work::ExecutionMode::kInline; };
enum class ResolutionStatus { kResolved,kNotFound,kAmbiguous,kUnavailable,kForbidden,kUnknown };
struct ResolutionResult { ResolutionStatus status=ResolutionStatus::kUnknown; std::optional<ResolvedWork> work; std::vector<std::string> reasons; };
class Resolver { public: bool add_operation(core::OperationDefinition op); void set_provider_registry(const infrastructure::ProviderSelectionRegistry* p){providers_=p;} ResolutionResult resolve(const core::OperationRequest& req) const; private: std::map<std::string,core::OperationDefinition> operations_; const infrastructure::ProviderSelectionRegistry* providers_=nullptr; };
using Handler=std::function<core::Outcome(const core::OperationRequest&,const ResolvedWork&,CancellationToken&)>;
class Dispatcher { public: bool register_handler(std::string capability,Handler h); core::Outcome dispatch(const core::OperationRequest&,const ResolvedWork&,CancellationToken&) const; private: std::map<std::string,Handler> handlers_; };
struct OperationHooks { std::function<core::Outcome(const core::OperationRequest&)> observe_before; std::function<core::Outcome(const core::OperationRequest&)> authorize; std::function<core::Outcome(const core::OperationRequest&)> observe_after; std::function<core::Outcome(const core::OperationRequest&)> verify; };
class OperationPipeline { public: OperationPipeline(const Resolver&r,const Dispatcher&d):resolver_(r),dispatcher_(d){} core::Outcome run(const core::OperationRequest&,CancellationToken&,const OperationHooks& hooks = OperationHooks{}) const; private: const Resolver& resolver_; const Dispatcher& dispatcher_; };
class Engine { public: Engine(RuntimeContext c,const Resolver&r,const Dispatcher&d):context_(std::move(c)),pipeline_(r,d){} core::Outcome submit(const core::OperationRequest&,const OperationHooks& hooks = OperationHooks{}); void stop_admission(){accepting_=false;} RuntimeContext& context(){return context_;} private: RuntimeContext context_; OperationPipeline pipeline_; bool accepting_=true; };
struct AttemptHistory { int number=0; core::Outcome outcome; };
struct JobRecord { work::Job job; std::vector<AttemptHistory> attempts; std::optional<core::Outcome> final_outcome; };
class JobRuntime { public: core::Outcome run(JobRecord&, const std::function<core::Outcome(int)>&, CancellationToken&) const; };
struct Activation { std::string id; std::string event_id; std::string trigger_id; core::OperationRequest request; };
class ActivationGate { public: std::optional<Activation> activate(const Event&,std::string trigger,core::OperationRequest,size_t max_inflight=64); void complete(const std::string&id); private: std::mutex mu_; std::set<std::string> seen_; size_t inflight_=0; };
class Coordinator { public: bool acquire(const std::string&resource,const std::string&owner); void release(const std::string&resource,const std::string&owner); private: std::mutex mu_; std::map<std::string,std::string> owners_; };
class ShutdownCoordinator { public: core::Outcome shutdown(Engine&,std::vector<std::shared_ptr<CancellationToken>>,std::chrono::milliseconds grace); };
enum class RecoveryClassification { kCompleted,kStillRunning,kInterrupted,kUnknown,kRecoverable,kRequiresVerification };
RecoveryClassification classify_recovery(const work::ExecutionRecord&, bool native_alive);
}
