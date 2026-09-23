#pragma once
#include <domains/development/infrastructure/contracts.hpp>
#include <algorithm>
#include <map>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::infrastructure {
struct ProviderInfo { std::string id; ProviderType type=ProviderType::kRuntime; std::vector<std::string> capabilities; int priority=0; bool available=true; bool authorized=true; std::string native_mechanism; };
struct ProviderSelectionContext { std::string capability; std::vector<std::string> preferred; std::optional<std::string> required_mechanism; bool require_authorized=true; };
struct ProviderSelectionResult { std::optional<ProviderInfo> provider; std::vector<std::string> rejected; bool success() const { return provider.has_value(); } };
class ProviderSelectionRegistry {
 public:
  bool register_provider(ProviderInfo p) { if(p.id.empty()||providers_.count(p.id)) return false; providers_.emplace(p.id,std::move(p)); return true; }
  ProviderSelectionResult select(const ProviderSelectionContext& c) const {
    ProviderSelectionResult r; std::vector<ProviderInfo> candidates;
    for (const auto& [id,p]:providers_) { if(std::find(p.capabilities.begin(),p.capabilities.end(),c.capability)==p.capabilities.end()){r.rejected.push_back(id+":capability");continue;} if(!p.available){r.rejected.push_back(id+":unavailable");continue;} if(c.require_authorized&&!p.authorized){r.rejected.push_back(id+":unauthorized");continue;} if(c.required_mechanism&&p.native_mechanism!=*c.required_mechanism){r.rejected.push_back(id+":mechanism");continue;} candidates.push_back(p); }
    std::stable_sort(candidates.begin(),candidates.end(),[&](const auto&a,const auto&b){auto rank=[&](const std::string&id){auto i=std::find(c.preferred.begin(),c.preferred.end(),id);return i==c.preferred.end()?999999:int(i-c.preferred.begin());}; auto ra=rank(a.id),rb=rank(b.id); return ra!=rb?ra<rb:a.priority>b.priority;});
    if(!candidates.empty()) { r.provider=candidates.front(); }
    return r;
  }
  size_t size() const{return providers_.size();}
 private: std::map<std::string,ProviderInfo> providers_;
};
}
