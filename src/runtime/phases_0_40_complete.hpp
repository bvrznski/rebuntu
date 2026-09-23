#pragma once
#include <chrono>
#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::platform::v0040 {
using Fields=std::map<std::string,std::string>;
enum class Epistemic { observed, derived, configured, unknown };
enum class Risk { read_only, low, medium, high, destructive };
struct Evidence { std::string source; std::string value; Epistemic epistemic{Epistemic::observed}; std::chrono::system_clock::time_point at{}; };
struct Entity { std::string id,type,name,state; Fields attributes; std::vector<Evidence> evidence; };
struct PhaseSpec { int major{},minor{}; std::string path,title; };
struct Coverage { int major{}; std::size_t prompts{}, mapped{}; bool implemented{}; std::vector<std::string> gaps; };
class RequirementIndex { public: explicit RequirementIndex(std::string root=".phases/PHASES"); const std::vector<PhaseSpec>& specs()const{return specs_;} std::vector<PhaseSpec> phase(int)const; std::vector<Coverage> coverage()const; bool complete_0_40()const; private:std::vector<PhaseSpec> specs_; };

struct HostSnapshot { std::vector<Entity> cpu,memory,processes,services,storage,network,gpus,packages,users,sessions; Fields kernel,pressure,power,desktop; std::vector<Entity> timeline; };
class LinuxInventory { public: HostSnapshot collect()const; std::vector<Entity> processes()const; std::vector<Entity> services()const; std::vector<Entity> storage()const; std::vector<Entity> network()const; std::vector<Entity> gpus()const; std::vector<Entity> packages(std::size_t limit=5000)const; std::vector<Entity> users()const; std::vector<Entity> timeline(std::size_t limit=200)const; };

struct ChangePlan { std::string id,domain,action,target; Fields desired; Risk risk{Risk::read_only}; bool privileged{}, reversible{}; std::vector<std::string> preconditions,steps,verification,rollback; };
struct Authorization { bool allowed{}; bool confirmation_required{}; std::string reason; };
class SafetyPolicy { public: Authorization authorize(const ChangePlan&,bool operator_confirmed,bool elevated)const; bool validate(const ChangePlan&)const; };

struct WorkflowStep { std::string id; std::set<std::string> after; unsigned retries{}; bool checkpoint{}; };
struct WorkflowPlan { std::string id; std::vector<WorkflowStep> steps; };
class WorkflowValidator { public: std::vector<std::string> validate(const WorkflowPlan&)const; std::vector<std::string> order(const WorkflowPlan&)const; };

struct Query { std::string text; std::optional<std::string> type; std::map<std::string,std::string> filters; std::size_t limit{50},offset{}; bool fuzzy{true}; };
struct SearchHit { Entity entity; double score{}; std::vector<std::string> reasons; };
struct SearchPage { std::vector<SearchHit> hits; std::map<std::string,std::size_t> facets; std::size_t total{}; bool partial{}; };
class SearchEngine { public: void index(const HostSnapshot&); void index(std::vector<Entity>); SearchPage search(const Query&)const; std::vector<std::string> complete(const std::string&,std::size_t limit=20)const; private:std::vector<Entity> entities_; };

struct CommandSpec { std::string name,domain,summary; Risk risk{Risk::read_only}; bool privileged{}; std::vector<std::string> aliases; };
class CommandRegistry { public: CommandRegistry(); void add(CommandSpec); std::optional<CommandSpec> resolve(const std::string&)const; std::vector<CommandSpec> discover(const std::string&)const; private:std::vector<CommandSpec> commands_; };


struct HealthSignal { std::string subsystem,metric; double value{},warn{},critical{}; Evidence evidence; };
struct HealthAssessment { std::string subsystem,state; double score{1.0}; std::vector<std::string> reasons; };
class HealthEngine { public: HealthAssessment assess(const std::string&,const std::vector<HealthSignal>&)const; };
struct TimelineEvent { std::chrono::system_clock::time_point at{}; std::string source,kind,subject,message; Fields attributes; double confidence{1.0}; };
class EventCorrelator { public: std::vector<std::vector<TimelineEvent>> correlate(std::vector<TimelineEvent>,std::chrono::seconds window)const; };
class SecretRedactor { public: std::string redact(std::string)const; Fields redact(Fields)const; };
struct FileTransactionResult { bool ok{}; std::string backup; std::string error; };
class ConfigurationTransaction { public: FileTransactionResult apply(const std::string&path,const std::string&content,bool confirmed)const; bool rollback(const std::string&path,const std::string&backup)const; };

struct AuditReport { bool ready{}; std::size_t prompt_count{}; std::map<int,std::size_t> phase_prompts; std::vector<std::string> issues; };
class System0040 { public: explicit System0040(std::string phase_root=".phases/PHASES"); RequirementIndex requirements; LinuxInventory inventory; SafetyPolicy policy; WorkflowValidator workflows; CommandRegistry commands; AuditReport audit()const; };
}
