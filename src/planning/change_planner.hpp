#pragma once
#include <runtime/phases_0_40_complete.hpp>
#include <functional>
namespace rebuntu::planning { using rebuntu::platform::v0040::ChangePlan; struct DesiredChange{std::string domain,target,property,value;bool privileged{},destructive{};}; class ChangePlanner{public: ChangePlan plan(const DesiredChange&)const; std::vector<std::string> validate(const ChangePlan&)const;}; }
