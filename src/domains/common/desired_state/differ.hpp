#pragma once
#include "../model.hpp"
namespace rebuntu::domains::common {
struct AttributeDelta { std::string key; std::optional<std::string> actual; std::string desired; };
struct DesiredStateDiff { std::vector<AttributeDelta> changes; bool converged() const{return changes.empty();} };
class DesiredStateDiffer { public: DesiredStateDiff diff(const DesiredResourceState& desired,const Resource& actual) const { DesiredStateDiff out; for(const auto& [k,v]:desired.attributes){auto i=actual.attributes.find(k);if(i==actual.attributes.end()||i->second!=v)out.changes.push_back({k,i==actual.attributes.end()?std::nullopt:std::optional<std::string>{i->second},v});} return out;} };
}