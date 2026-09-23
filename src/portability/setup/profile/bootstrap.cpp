#include "bootstrap.hpp"
namespace rebuntu::setup::profile {
Derived derive(const Input&i){Derived o;auto apply=[&](const auto&m,const char*s){for(auto&[k,v]:m){o.values[k]=v;o.provenance[k]=s;}};apply(i.discovered,"discovery");apply(i.preferences,"preference");apply(i.explicit_values,"explicit");apply(i.policy,"policy");return o;}
}
