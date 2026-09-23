#pragma once
#include <runtime/phases_46_53.hpp>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::platform::v5462 {
using Fields=rebuntu::platform::Fields; using Clock=std::chrono::system_clock;
enum class Availability { available, unavailable, degraded, unknown };
struct Capability { std::string id,provider; Availability state{Availability::unknown}; std::set<std::string> prerequisites,blockers; Clock::time_point observed{Clock::now()}; std::chrono::seconds ttl{60}; Fields attributes; };
struct Affordance { std::string action,target; bool possible{}; std::vector<std::string> why_not; std::set<std::string> capabilities; };
class CapabilityModel { public: void observe(Capability); void invalidate(const std::string&); std::optional<Capability> get(const std::string&)const; Affordance afford(std::string,std::string,const std::set<std::string>&)const; std::vector<Capability> all()const; private:std::map<std::string,Capability> caps_; };

enum class GoalState { proposed,active,satisfied,blocked,abandoned,failed };
struct Goal { std::string id,description; Fields desired; int priority{}; GoalState state{GoalState::proposed}; std::set<std::string> constraints; Clock::time_point deadline{}; };
struct WorldState { Fields values; std::uint64_t revision{}; };
struct PlanStep { std::string id,action,target; Fields effects; std::set<std::string> requirements; double cost{1}; bool reversible{true}; };
struct Plan { std::string id,goal; std::vector<PlanStep> steps; double cost{}; std::uint64_t based_on_revision{}; bool valid{}; std::vector<std::string> blockers; };
class GoalManager { public: bool put(Goal); bool activate(const std::string&); bool transition(const std::string&,GoalState); std::optional<Goal> get(const std::string&)const; std::vector<Goal> active()const; private:std::map<std::string,Goal> goals_; };
class Planner { public: using Operator=std::function<std::vector<PlanStep>(const Goal&,const WorldState&,const CapabilityModel&)>; void add_operator(std::string,Operator); Plan synthesize(const Goal&,const WorldState&,const CapabilityModel&)const; Plan replan(const Plan&,const Goal&,const WorldState&,const CapabilityModel&)const; private:std::map<std::string,Operator> ops_;mutable std::size_t seq_{}; };

enum class Severity { info,warning,error,critical };
struct Constraint { std::string id,description; Severity severity{Severity::error}; std::function<bool(const WorldState&)> predicate; bool hard{true}; };
struct ContractResult { bool satisfied{}; std::vector<std::string> violations,warnings; };
class ContractEngine { public: void add(Constraint); ContractResult evaluate(const WorldState&)const; private:std::vector<Constraint> cs_; };

struct Impact { std::string subject,effect; Severity severity{Severity::info}; double confidence{1}; bool reversible{true}; };
struct Change { std::string id,action,target; Fields before,after; bool privileged{},destructive{}; };
class ImpactAnalyzer { public: using Analyzer=std::function<std::vector<Impact>(const Change&,const WorldState&)>; void add(std::string,Analyzer); std::vector<Impact> analyze(const Change&,const WorldState&)const; bool acceptable(const std::vector<Impact>&,Severity max=Severity::error)const; private:std::map<std::string,Analyzer> analyzers_; };

enum class TxState { created,prepared,committing,committed,verifying,verified,rolling_back,rolled_back,failed,indeterminate };
struct Transition { std::string id; Change change; TxState state{TxState::created}; std::vector<std::string> journal; };
class TransactionEngine { public: using Apply=std::function<bool(const Change&)>; using Verify=std::function<bool(const Change&)>; using Rollback=std::function<bool(const Change&)>; Transition begin(Change); bool prepare(Transition&,const ContractResult&,const std::vector<Impact>&); bool commit(Transition&,Apply,Verify,Rollback); bool rollback(Transition&,Rollback); private:std::size_t seq_{}; };

struct Incident { std::string id,subject,symptom; Severity severity{Severity::error}; unsigned attempts{}; bool resolved{}; std::vector<std::string> history; };
struct Repair { std::string id; std::set<std::string> symptoms; std::function<bool(Incident&)> action; unsigned max_attempts{1}; bool destructive{}; };
class RecoveryEngine { public: void register_repair(Repair); bool recover(Incident&,bool destructive_authorized=false)const; private:std::vector<Repair> repairs_; };

struct HealthSignal { std::string name; double value{},lower{},upper{}; double weight{1}; Clock::time_point observed{Clock::now()}; };
struct HealthReport { double score{1}; bool stable{true}; std::vector<std::string> violations; };
class Homeostasis { public: void observe(HealthSignal); HealthReport assess()const; std::vector<std::string> corrections()const; private:std::map<std::string,HealthSignal> signals_; };

struct ReconcileResult { std::string goal; bool converged{}; unsigned iterations{}; std::vector<std::string> actions,blockers; };
class Reconciler { public: ReconcileResult reconcile(Goal&,WorldState&,const CapabilityModel&,Planner&,const ContractEngine&,unsigned max_iterations=8)const; };

class DesiredStateRuntime { public: CapabilityModel capabilities;GoalManager goals;Planner planner;ContractEngine contracts;ImpactAnalyzer impacts;TransactionEngine transactions;RecoveryEngine recovery;Homeostasis homeostasis;Reconciler reconciler; WorldState world; bool set(std::string,std::string); ReconcileResult maintain(const std::string&,unsigned max_iterations=8); };

struct Coverage { int phase{}; std::size_t prompt_count{}; bool implemented{}; };
class PhaseCoverage { public: explicit PhaseCoverage(std::string root); const std::vector<Coverage>& rows()const{return rows_;} bool complete()const; private:std::vector<Coverage> rows_; };
}
