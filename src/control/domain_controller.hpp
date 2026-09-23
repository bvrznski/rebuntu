#pragma once
#include <semantics/entities/state_store.hpp>
#include <planning/change_planner.hpp>
namespace rebuntu::management { enum class Domain{process,service,storage,network,gpu,package,configuration,secrets,identity,shell,terminal,development}; struct Request{Domain domain;std::string target,property,value;}; class DomainController{public:explicit DomainController(model::StateStore& s):state_(s){} platform::v0040::ChangePlan prepare(const Request&)const;void observe(const Request&,std::string source="controller");private:model::StateStore&state_;}; }
