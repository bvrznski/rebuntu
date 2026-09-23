#pragma once
#include <runtime/phases_30_39.hpp>
#include <chrono>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::platform::v4045 {
using Fields=rebuntu::platform::Fields;
enum class Truth { no, yes, unknown };
struct Evidence { std::string source,subject,predicate,value; double confidence{1.0}; std::chrono::system_clock::time_point observed{}; };
struct SearchResult { std::string id,domain,title; double score{}; Fields fields; std::vector<Evidence> evidence; };
struct Query { std::string text; std::set<std::string> domains; Fields filters; std::size_t limit{50}; };
class SearchSystem { public: using Provider=std::function<std::vector<SearchResult>(const Query&)>; void add_provider(std::string,Provider); std::vector<SearchResult> search(const Query&)const; std::vector<std::string> providers()const; private:std::map<std::string,Provider> providers_; };
enum class RunState { queued,running,paused,succeeded,failed,cancelled,unknown };
struct WorkflowNode { std::string id; std::vector<std::string> after; std::function<bool()> action; unsigned retries{}; };
struct WorkflowRun { std::string id; RunState state{RunState::queued}; std::vector<std::string> completed,failed; };
class WorkflowSystem { public: bool define(std::string,std::vector<WorkflowNode>); WorkflowRun run(const std::string&); std::optional<WorkflowRun> status(const std::string&)const; private:std::map<std::string,std::vector<WorkflowNode>> defs_;std::map<std::string,WorkflowRun> runs_;std::size_t seq_{}; };
struct GraphNode { std::string id,type; Fields properties; };
struct GraphEdge { std::string from,to,type; std::vector<Evidence> evidence; };
class KnowledgeGraph { public: bool upsert(GraphNode); bool relate(GraphEdge); std::optional<GraphNode> get(const std::string&)const; std::vector<GraphNode> neighbors(const std::string&,const std::string& type="")const; std::vector<std::string> path(const std::string&,const std::string&,std::size_t max_depth=8)const; private:std::map<std::string,GraphNode> nodes_;std::vector<GraphEdge> edges_; };
struct Recommendation { std::string id,summary; double confidence{}; std::vector<Evidence> evidence; Fields expected_effects; bool actionable{false}; };
class OperatorIntelligence { public: Recommendation diagnose(std::string,const std::vector<Evidence>&)const; std::vector<Recommendation> rank(std::vector<Recommendation>)const; };
struct Adaptation { std::string id,target,parameter,old_value,new_value,reason; double expected_gain{}; bool reversible{true},privileged{false}; };
class AdaptiveWorkstation { public: void protect(std::string); bool propose(Adaptation); bool authorize(const std::string&,bool operator_approved); bool apply(const std::string&); bool rollback(const std::string&); std::optional<Adaptation> current(const std::string&)const; private:std::set<std::string> protected_;std::map<std::string,Adaptation> proposed_,applied_;std::set<std::string> authorized_; };
enum class OperationState { planned,validated,authorized,executing,verified,rolled_back,rejected,failed };
struct Operation { std::string id,domain,action,target; Fields desired; bool mutating{false},privileged{false},destructive{false}; OperationState state{OperationState::planned}; std::vector<std::string> journal; };
class UnifiedControlPlane { public: UnifiedControlPlane(); SearchSystem search; WorkflowSystem workflows; KnowledgeGraph graph; OperatorIntelligence intelligence; AdaptiveWorkstation adaptive; Operation plan(std::string,std::string,std::string,Fields={},bool=false,bool=false,bool=false); bool validate(Operation&); bool authorize(Operation&,bool operator_approved); bool execute(Operation&); bool verify(Operation&); bool rollback(Operation&); std::vector<Operation> history()const; private:std::vector<Operation> history_;std::size_t seq_{}; };
struct PhaseInfo { int major{},minor{}; std::string title,file; };
class PhaseRegistry { public: explicit PhaseRegistry(std::string root=".phases"); const std::vector<PhaseInfo>& all()const{return phases_;} std::size_t count(int major)const; bool complete()const; private:std::vector<PhaseInfo> phases_; };
}
