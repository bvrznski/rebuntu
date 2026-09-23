#include "control/checkpoints/durable_store.hpp"
#include "control/reconciliation/coordination/durable_cross_domain.hpp"
#include "control/verification/evidence/durable_chain.hpp"
#include "control/verification/evidence/transaction_binding.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace rebuntu;
int main(){namespace fs=std::filesystem;using namespace control::reconciliation::coordination;auto cp=fs::temp_directory_path()/"rebuntu-xiv-cp.log";auto ev=fs::temp_directory_path()/"rebuntu-xiv-ev.log";fs::remove(cp);fs::remove(ev);
 control::checkpoints::DurableStore store(cp);control::verification::evidence::DurableEvidenceChain chain(ev);control::verification::evidence::TransactionEvidenceBinding binding(store,chain);int applies=0,rollbacks=0;
 WorkItem w{"network","networking",{},[&]{++applies;common_result r;r.converged=true;domains::common::OperationVerificationEvidence e;e.operation_fingerprint="netlink:set-up#1";e.predicate="state=up";e.observed="up";e.passed=true;r.operation_evidence.push_back(e);return r;},[&]{++rollbacks;return true;}};
 auto first=DurableCrossDomainCoordinator(store,binding).reconcile("tx",{w});assert(first.reconciliation.converged&&applies==1);auto hist=store.transaction("tx");bool has_verified=false;for(const auto&r:hist)if(r.work_id=="network"&&r.stage==control::checkpoints::DurableStage::verified)has_verified=true;assert(has_verified);auto evidence=chain.load();assert(evidence.size()==1&&evidence[0].operation=="netlink:set-up#1");std::cout<<"PRODUCTION_DURABLE_EVIDENCE_SINK_PASS\n";
 auto resumed=DurableCrossDomainCoordinator(store,binding).reconcile("tx",{w});assert(resumed.reconciliation.converged&&applies==1&&resumed.recovered_work.size()==1);std::cout<<"RESUME_FROM_LAST_VERIFIED_POSTCONDITION_PASS\n";
 fs::remove(cp);fs::remove(ev);control::checkpoints::DurableStore torn(cp);torn.append({"crash","storage",control::checkpoints::DurableStage::prepared,0});{std::ofstream o(cp,std::ios::app|std::ios::binary);o<<"crash\tstorage\tapplied\t1\tdead";}assert(torn.recover_torn_tail());auto recovered=torn.load();assert(recovered.size()==1&&recovered[0].stage==control::checkpoints::DurableStage::prepared);std::cout<<"TORN_CHECKPOINT_TAIL_RECOVERY_PASS\n";
 {std::ofstream o(cp,std::ios::app|std::ios::binary);o<<"crash\tstorage\tapplied\t1\tdeadbeefdeadbeef\n";}bool corrupt=false;try{(void)torn.load(true);}catch(const std::runtime_error&){corrupt=true;}assert(corrupt);std::cout<<"CHECKPOINT_CORRUPTION_FAIL_CLOSED_PASS\n";fs::remove(cp);fs::remove(ev);(void)rollbacks;}
