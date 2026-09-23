#pragma once
#include <runtime/phases_40_45.hpp>
#include <chrono>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::platform::v4653 {
using Fields=rebuntu::platform::Fields;
using Clock=std::chrono::system_clock;

enum class Decision { allow, deny, clarify, justify, defer };
enum class Risk { negligible, low, medium, high, critical };
struct Provenance { std::string source, principal, mechanism; Clock::time_point observed{Clock::now()}; double confidence{1.0}; };
struct Principal { std::string id; std::set<std::string> roles, capabilities; bool local{true}; };
struct TaskContext { std::string cwd, session, host, purpose; Fields facts; std::vector<Provenance> provenance; Clock::time_point captured{Clock::now()}; std::chrono::seconds ttl{300}; bool fresh()const; };
struct IntentCandidate { std::string verb,target; Fields arguments; double confidence{}; bool mutating{},privileged{},destructive{}; std::vector<std::string> ambiguities; };
struct Task { std::string id,origin,verb,target; Principal requester; TaskContext context; Fields arguments; Risk risk{Risk::low}; bool mutating{},privileged{},destructive{},reversible{true}; std::set<std::string> required_capabilities; std::vector<std::string> delegation_chain; };
struct PolicyRule { std::string id; int priority{}; std::set<std::string> origins,verbs,targets,roles,required_context; Decision decision{Decision::deny}; Risk max_risk{Risk::critical}; bool require_local{},require_fresh_context{},require_reversible{}; };
struct PolicyResult { Decision decision{Decision::deny}; std::string rule,reason; std::vector<std::string> missing; };
class TaskPolicyEngine { public: void add(PolicyRule); PolicyResult evaluate(const Task&)const; private:std::vector<PolicyRule> rules_; };

class ContextEngine { public: using Source=std::function<std::optional<std::pair<std::string,Provenance>>(const std::string&)>; void source(std::string,Source); TaskContext capture(std::string cwd,std::string session,std::string host,const std::set<std::string>& keys)const; std::vector<std::string> conflicts(const TaskContext&)const; private:std::map<std::string,Source> sources_; };
class NaturalLanguageOperator { public: using SemanticProvider=std::function<std::vector<IntentCandidate>(const std::string&,const TaskContext&)>; explicit NaturalLanguageOperator(v4045::UnifiedControlPlane&); void semantic_provider(SemanticProvider); void policy(TaskPolicyEngine*); struct Reply { Decision decision{Decision::deny}; std::string message; std::optional<Task> task; std::optional<v4045::Operation> operation; std::vector<std::string> alternatives; }; Reply ask(const std::string&,const Principal&,const TaskContext&,bool operator_approved=false); private:v4045::UnifiedControlPlane& control_;SemanticProvider semantic_;TaskPolicyEngine* policy_{};std::size_t seq_{}; };

struct GuiRequest { std::string surface,action,target; Fields parameters; Principal principal; TaskContext context; };
class GuiBoundary { public: explicit GuiBoundary(NaturalLanguageOperator&); NaturalLanguageOperator::Reply submit(const GuiRequest&,bool approved=false); std::vector<std::string> surfaces()const; private:NaturalLanguageOperator& ask_; };

struct PlatformInfo { std::string os,kernel,arch,hostname; Fields capabilities; };
class PlatformAdapter { public: virtual ~PlatformAdapter()=default; virtual PlatformInfo inspect()const=0; virtual bool supports(const std::string&)const=0; virtual std::optional<std::string> read(const std::string&)const=0; };
class LinuxAdapter final: public PlatformAdapter { public: PlatformInfo inspect()const override; bool supports(const std::string&)const override; std::optional<std::string> read(const std::string&)const override; };

struct Node { std::string id,endpoint; std::set<std::string> capabilities; Clock::time_point seen{Clock::now()}; bool quarantined{},draining{}; };
struct RemoteResult { bool accepted{},completed{},indeterminate{}; std::string detail; };
class Fabric { public: bool admit(Node); bool remove(const std::string&); bool quarantine(const std::string&,bool=true); std::vector<Node> members()const; std::optional<Node> choose(const std::set<std::string>&)const; RemoteResult dispatch(const Task&,const std::string&,const std::function<RemoteResult(const Task&,const Node&)>&)const; private:std::map<std::string,Node> nodes_; };

struct SystemIdentity { std::string id,fingerprint,public_material; std::uint64_t generation{}; bool revoked{}; };
struct AssociationGrant { std::string id,peer; std::set<std::string> capabilities; Clock::time_point expires{}; bool revoked{}; };
class AssociationManager { public: bool local(SystemIdentity); bool associate(SystemIdentity peer,std::string proof); std::optional<AssociationGrant> grant(const std::string&,std::set<std::string>,std::chrono::seconds); bool authorize(const std::string&,const std::string&)const; bool revoke(const std::string&); private:std::optional<SystemIdentity> local_;std::map<std::string,SystemIdentity> peers_;std::map<std::string,AssociationGrant> grants_;std::size_t seq_{}; };

enum class Secrecy:int { public_data=0,internal=1,confidential=2,secret=3 };
enum class Integrity:int { untrusted=0,normal=1,high=2,critical=3 };
struct Label { Secrecy secrecy{Secrecy::internal}; Integrity integrity{Integrity::normal}; std::set<std::string> compartments; };
class InformationFlow { public: static bool can_read(const Label& subject,const Label& object); static bool can_write(const Label& subject,const Label& object); static bool can_flow(const Label& from,const Label& to); };

struct Coverage { int phase{}; std::size_t prompt_count{}; std::string manifest_name; bool architecture_present{},implemented{}; };
class PhaseCoverage { public: explicit PhaseCoverage(std::string root); const std::vector<Coverage>& rows()const{return rows_;} bool complete()const; private:std::vector<Coverage> rows_; };
}
