#pragma once
#include "../../../domains/common/reconciliation/domain_reconciler.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <stdexcept>
namespace rebuntu::control::reconciliation::coordination {
using common_result=domains::common::ReconcileResult;
struct WorkItem { std::string id; std::string domain; std::vector<std::string> depends_on; std::function<common_result()> apply; std::function<bool()> rollback; };
struct CrossDomainResult { bool converged{false}; bool rolled_back{false}; std::vector<std::string> order; std::map<std::string,common_result> results; std::vector<std::string> errors; };
class CrossDomainCoordinator {
 static std::vector<std::string> order(const std::vector<WorkItem>& items){
  std::map<std::string,const WorkItem*> by;for(const auto& i:items){if(i.id.empty()||!by.emplace(i.id,&i).second)throw std::invalid_argument("duplicate/empty work id");}
  std::map<std::string,std::size_t> indegree;std::map<std::string,std::vector<std::string>> next;for(const auto& [id,_]:by)indegree[id]=0;
  for(const auto& i:items)for(const auto& d:i.depends_on){if(!by.count(d))throw std::invalid_argument("unknown dependency: "+d);++indegree[i.id];next[d].push_back(i.id);}
  std::set<std::string> ready;for(const auto& [id,n]:indegree)if(n==0)ready.insert(id);std::vector<std::string> out;
  while(!ready.empty()){auto id=*ready.begin();ready.erase(ready.begin());out.push_back(id);for(const auto& n:next[id])if(--indegree[n]==0)ready.insert(n);}
  if(out.size()!=items.size()){throw std::invalid_argument("cross-domain dependency cycle");} return out;
 }
public:
 CrossDomainResult reconcile(const std::vector<WorkItem>& items) const {
  CrossDomainResult out;try{out.order=order(items);}catch(const std::exception& e){out.errors.push_back(e.what());return out;}
  std::map<std::string,const WorkItem*> by;for(const auto& i:items)by[i.id]=&i;std::vector<const WorkItem*> completed;
  for(const auto& id:out.order){const auto* w=by.at(id);if(!w->apply){out.errors.push_back(id+": missing reconcile callback");break;}auto r=w->apply();out.results.emplace(id,r);if(!r.converged){out.errors.push_back(id+": did not converge");break;}completed.push_back(w);}
  if(out.errors.empty()){out.converged=true;return out;}
  bool attempted=false;for(auto i=completed.rbegin();i!=completed.rend();++i){if((*i)->rollback){attempted=true;if(!(*i)->rollback())out.errors.push_back((*i)->id+": cross-domain rollback failed");}}
  out.rolled_back=attempted;return out;
 }
};
}
