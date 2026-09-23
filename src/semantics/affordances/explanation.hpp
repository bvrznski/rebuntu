#pragma once
#include "model.hpp"
#include <sstream>
namespace rebuntu::semantics::affordances {
inline std::string explain(const AffordanceResult& r){ if(r.executable()) return "affordance executable: capability evidence is fresh, prerequisites are satisfied, and security authorized the verb"; std::ostringstream o;o<<"affordance blocked"; for(const auto& b:r.blockers)o<<"; "<<b.subject<<": "<<b.detail; return o.str(); }
}
