#pragma once
#include <semantics/entities/state_store.hpp>
#include <planning/change_planner.hpp>
#include <map>
namespace rebuntu::reconciliation { struct DesiredState{std::string subject;std::map<std::string,std::string>properties;}; struct Drift{std::string property,observed,desired;}; class Reconciler{public:std::vector<Drift> diff(const DesiredState&,const model::StateStore&)const;std::vector<platform::v0040::ChangePlan> plans(const DesiredState&,const model::StateStore&,const planning::ChangePlanner&)const;}; }
