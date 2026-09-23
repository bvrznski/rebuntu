#pragma once
#include "../model.hpp"
namespace rebuntu::domains::common::requirements {
struct Resolution { RequirementResult requirements; std::vector<std::string> missing_capabilities; bool ready() const {return requirements.satisfied&&missing_capabilities.empty();} };
inline Resolution resolve(const DomainModel& m,const std::vector<std::string>& verbs){ Resolution r; r.requirements=evaluate(m.resource,m.requirements); for(const auto& v:verbs) if(!affords(m,v)) r.missing_capabilities.push_back(v); return r; }
}
