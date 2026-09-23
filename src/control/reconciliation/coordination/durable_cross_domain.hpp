#pragma once
#include "cross_domain.hpp"
#include "../../checkpoints/durable_store.hpp"
#include "../../verification/evidence/transaction_binding.hpp"
#include <map>
#include <set>

namespace rebuntu::control::reconciliation::coordination {
struct DurableRunResult { CrossDomainResult reconciliation; bool resumed{false}; std::vector<std::string> recovered_work; };
class DurableCrossDomainCoordinator {
    checkpoints::DurableStore& store_;
    verification::evidence::TransactionEvidenceBinding* evidence_{nullptr};
public:
    explicit DurableCrossDomainCoordinator(checkpoints::DurableStore& store):store_(store){}
    DurableCrossDomainCoordinator(checkpoints::DurableStore& store, verification::evidence::TransactionEvidenceBinding& evidence):store_(store),evidence_(&evidence){}
    DurableRunResult reconcile(std::string transaction_id,const std::vector<WorkItem>& items) const {
        if(transaction_id.empty())throw std::invalid_argument("empty transaction id");
        auto history=store_.transaction(transaction_id);std::set<std::string> applied,verified;std::size_t sequence=history.size();
        for(const auto& r:history){
            if(r.stage==checkpoints::DurableStage::applied)applied.insert(r.work_id);
            if(r.stage==checkpoints::DurableStage::verified){applied.insert(r.work_id);verified.insert(r.work_id);}
            if(r.stage==checkpoints::DurableStage::rolled_back){applied.erase(r.work_id);verified.erase(r.work_id);}
        }
        DurableRunResult out;out.resumed=!history.empty();std::vector<WorkItem> wrapped;wrapped.reserve(items.size());
        for(const auto& item:items){auto w=item;auto original_apply=item.apply;auto original_rollback=item.rollback;
            w.apply=[&,id=item.id,original_apply](){
                const bool durable_verified=evidence_?verified.count(id)!=0:applied.count(id)!=0;
                if(durable_verified){common_result r;r.converged=true;out.recovered_work.push_back(id);return r;}
                store_.append({transaction_id,id,checkpoints::DurableStage::prepared,sequence++});auto r=original_apply?original_apply():common_result{};
                if(!r.converged){store_.append({transaction_id,id,checkpoints::DurableStage::failed,sequence++});return r;}
                const auto applied_sequence=sequence;store_.append({transaction_id,id,checkpoints::DurableStage::applied,sequence++});applied.insert(id);
                if(evidence_){
                    try{
                        if(r.operation_evidence.empty()) evidence_->append(transaction_id,applied_sequence,id,"reconciliation=converged","converged",true);
                        else for(const auto& ev:r.operation_evidence)evidence_->append(transaction_id,applied_sequence,ev.operation_fingerprint,ev.predicate,ev.observed,ev.passed);
                        evidence_->validate(transaction_id);
                        store_.append({transaction_id,id,checkpoints::DurableStage::verified,sequence++});verified.insert(id);
                    }catch(const std::exception& e){r.converged=false;r.errors.push_back(std::string("durable verification evidence failure: ")+e.what());store_.append({transaction_id,id,checkpoints::DurableStage::failed,sequence++});}
                }
                return r;
            };
            w.rollback=[&,id=item.id,original_rollback](){store_.append({transaction_id,id,checkpoints::DurableStage::rollback_pending,sequence++});bool ok=original_rollback&&original_rollback();store_.append({transaction_id,id,ok?checkpoints::DurableStage::rolled_back:checkpoints::DurableStage::failed,sequence++});if(ok){applied.erase(id);verified.erase(id);}return ok;};wrapped.push_back(std::move(w));}
        out.reconciliation=CrossDomainCoordinator{}.reconcile(wrapped);
        if(out.reconciliation.converged){store_.append({transaction_id,"__transaction__",checkpoints::DurableStage::committed,sequence++});}
        return out;
    }
};
} // namespace rebuntu::control::reconciliation::coordination
