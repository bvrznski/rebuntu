#pragma once
#include <runtime/phases_0_40_complete.hpp>
#include <set>
namespace rebuntu::policy { struct Context{std::string actor;bool elevated{},interactive{};std::set<std::string>capabilities;}; struct Decision{bool allowed{},confirmation{};std::vector<std::string>reasons;}; class PolicyEngine{public: Decision evaluate(const platform::v0040::ChangePlan&,const Context&)const;}; }
