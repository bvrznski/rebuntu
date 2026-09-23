#pragma once
#include "../model.hpp"
namespace rebuntu::domains::common {
enum class HealthState { healthy,degraded,failed,unknown };
struct HealthAssessment { HealthState state{HealthState::unknown}; std::vector<std::string> reasons; };
class HealthEvaluator { public: HealthAssessment evaluate(const Health& h) const {HealthAssessment a;if(h.signals.empty()){a.reasons.push_back("no health evidence");return a;}a.state=HealthState::healthy;for(const auto&s:h.signals){if(s.status=="failed"){a.state=HealthState::failed;a.reasons.push_back(s.name+": "+s.detail);}else if(s.status=="degraded"&&a.state!=HealthState::failed){a.state=HealthState::degraded;a.reasons.push_back(s.name+": "+s.detail);}}return a;} };
}