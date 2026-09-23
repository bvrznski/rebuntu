#include "model.hpp"
namespace rebuntu::setup::configuration {
Diff diff(const Document& c,const Document& d){ Diff out; std::map<std::string,std::string> cm,dm; for(auto&e:c.entries)cm[e.key]=e.value; for(auto&e:d.entries)dm[e.key]=e.value; for(auto&e:d.entries){auto i=cm.find(e.key);if(i==cm.end()||i->second!=e.value)out.set.push_back(e);} if(d.ownership!=Ownership::user_owned) for(auto&e:c.entries) if(!dm.count(e.key))out.remove.push_back(e.key); return out; }
}
