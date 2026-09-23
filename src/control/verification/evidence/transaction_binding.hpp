#pragma once
#include "durable_chain.hpp"
#include "../../checkpoints/durable_store.hpp"
#include <set>
#include <stdexcept>
#include <string_view>
namespace rebuntu::control::verification::evidence {
class TransactionEvidenceBinding {
 checkpoints::DurableStore& checkpoints_; DurableEvidenceChain& evidence_;
public:
 TransactionEvidenceBinding(checkpoints::DurableStore& c,DurableEvidenceChain& e):checkpoints_(c),evidence_(e){}
 DurableEvidenceRecord append(std::string transaction,std::size_t checkpoint_sequence,std::string operation,std::string predicate,std::string observed,bool passed)const{
  auto history=checkpoints_.transaction(transaction);bool bound=false;for(const auto&r:history)if(r.sequence==checkpoint_sequence){bound=true;break;}if(!bound)throw std::runtime_error("evidence references unknown checkpoint");
  return evidence_.append({0,std::move(transaction),checkpoint_sequence,std::move(operation),std::move(predicate),std::move(observed),passed,{},{}});
 }
 void validate(std::string_view transaction)const{
  std::set<std::size_t> seq;for(const auto&r:checkpoints_.transaction(transaction))seq.insert(r.sequence);for(const auto&e:evidence_.load())if(e.transaction==transaction&&!seq.count(e.checkpoint_sequence))throw std::runtime_error("orphan durable verification evidence");
 }
};
}
