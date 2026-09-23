#pragma once
#include <chrono>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::workflow {
enum class TriggerKind{event,condition,schedule,path,device,socket,manual};enum class RunState{idle,queued,running,succeeded,failed,cooldown,disabled};struct Trigger{TriggerKind kind;std::string expression;};struct Policy{unsigned max_retries{3};std::chrono::milliseconds cooldown{0};bool enabled{true};};struct Automaton{std::string id,name;Trigger trigger;Policy policy;std::function<bool()>action;RunState state{RunState::idle};unsigned failures{0};std::chrono::steady_clock::time_point last_run{};};struct RunEvidence{std::string automaton_id;RunState result;unsigned attempt;std::string detail;};
class AutomationRuntime{public:bool register_automaton(Automaton);bool remove(std::string_view);std::vector<std::string>discover()const;std::optional<RunEvidence>trigger(std::string_view id);std::vector<RunEvidence>evidence()const{return evidence_;}private:std::map<std::string,Automaton>automata_;std::vector<RunEvidence>evidence_;};
struct WorkflowStep{std::string id;std::function<bool()>action;std::vector<std::string>depends_on;};struct Workflow{std::string id;std::vector<WorkflowStep>steps;};class WorkflowRuntime{public:bool run(const Workflow&);const std::vector<std::string>&completed()const{return completed_;}private:std::vector<std::string>completed_;};
}