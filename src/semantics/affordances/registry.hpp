#pragma once
#include "model.hpp"
#include <algorithm>
#include <map>
#include <optional>
#include <string_view>

namespace rebuntu::semantics::affordances {
class Registry {
public:
    bool advertise(CapabilityInstance value){ if(value.definition.id.empty()||value.definition.provider.empty()||value.target_id.empty()) return false; auto key=value.definition.id+"@"+value.target_id+"#"+value.definition.provider; return values_.insert_or_assign(std::move(key),std::move(value)).second; }
    std::vector<CapabilityInstance> query(std::string_view verb,std::string_view target_kind,std::chrono::system_clock::time_point now,std::size_t limit=128) const { std::vector<CapabilityInstance> out; for(const auto& [_,v]:values_){if(out.size()>=limit)break;if(!v.definition.verbs.contains(std::string(verb)))continue;if(!v.definition.target_kinds.empty()&&!v.definition.target_kinds.contains(std::string(target_kind)))continue;bool fresh=std::any_of(v.evidence.begin(),v.evidence.end(),[&](const Evidence&e){return e.fresh(now);});if(fresh)out.push_back(v);} std::sort(out.begin(),out.end(),[](const auto&a,const auto&b){if(a.state!=b.state)return a.state<b.state;return a.definition.id<b.definition.id;}); return out; }
    std::size_t invalidate_authority(std::string_view authority){std::size_t n=0;for(auto& [_,v]:values_)for(auto& e:v.evidence)if(e.authority==authority){e.ttl=std::chrono::seconds{0};++n;}return n;}
    std::size_t invalidate_generation(std::uint64_t generation){std::size_t n=0;for(auto& [_,v]:values_)for(auto& e:v.evidence)if(e.generation<generation){e.ttl=std::chrono::seconds{0};++n;}return n;}
    std::size_t size() const noexcept{return values_.size();}
private: std::map<std::string,CapabilityInstance> values_;
};
}
