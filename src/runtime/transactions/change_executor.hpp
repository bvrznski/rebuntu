#pragma once
#include <security/policy/policy_engine.hpp>
#include <functional>
namespace rebuntu::transactions { struct StepResult{std::string step;bool ok{};std::string detail;}; struct ExecutionResult{bool ok{};bool rolled_back{};std::vector<StepResult>steps;}; using StepFn=std::function<bool(const std::string&)>; class ChangeExecutor{public:ExecutionResult execute(const platform::v0040::ChangePlan&,const policy::Decision&,StepFn apply,StepFn rollback)const;}; }
