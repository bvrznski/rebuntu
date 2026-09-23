#pragma once
#include "../model.hpp"
#include <queue>
namespace rebuntu::domains::common {
struct TopologyAnalysis { bool acyclic{true}; std::vector<std::string> order; std::vector<std::string> dangling; std::vector<std::string> cycles; };
class TopologyAnalyzer { public: TopologyAnalysis analyze(const Topology& t,const std::string& dependency_predicate="depends_on") const {
 TopologyAnalysis out; std::map<std::string,std::size_t> indegree; std::map<std::string,std::vector<std::string>> reverse;
 for(const auto& [id,_]:t.nodes) indegree[id]=0;
 for(const auto& e:t.edges){if(!t.nodes.contains(e.subject)||!t.nodes.contains(e.object)){out.dangling.push_back(e.subject+" -> "+e.object);continue;} if(e.predicate==dependency_predicate){++indegree[e.subject];reverse[e.object].push_back(e.subject);}}
 std::priority_queue<std::string,std::vector<std::string>,std::greater<>> q; for(const auto& [id,n]:indegree)if(n==0)q.push(id);
 while(!q.empty()){auto n=q.top();q.pop();out.order.push_back(n);for(const auto& x:reverse[n])if(--indegree[x]==0)q.push(x);} if(out.order.size()!=t.nodes.size()){out.acyclic=false;for(const auto& [id,n]:indegree)if(n)out.cycles.push_back(id);} return out;
 }};
}