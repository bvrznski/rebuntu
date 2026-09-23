#include "invariants.hpp"
namespace rebuntu::runtime::installation::verification { Report verify(const std::vector<Invariant>& is){Report r;r.usable=true;for(auto&i:is)if(!i.check()){r.usable=false;r.failed.push_back(i.id);}return r;} }
