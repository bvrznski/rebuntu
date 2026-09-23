#include "control/checkpoints/durable_store.hpp"
#include "control/verification/evidence/durable_chain.hpp"
#include "control/verification/evidence/transaction_binding.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace rebuntu::control;
int main(){namespace fs=std::filesystem;auto cp=fs::temp_directory_path()/"rebuntu-xiii-checkpoints.log";auto ev=fs::temp_directory_path()/"rebuntu-xiii-evidence.log";fs::remove(cp);fs::remove(ev);
 checkpoints::DurableStore store(cp);store.append({"tx","network",checkpoints::DurableStage::prepared,0});store.append({"tx","network",checkpoints::DurableStage::applied,1});verification::evidence::DurableEvidenceChain chain(ev);verification::evidence::TransactionEvidenceBinding binding(store,chain);auto r=binding.append("tx",1,"netlink:set-up","state=up","up",true);assert(r.checkpoint_sequence==1);binding.validate("tx");bool rejected=false;try{(void)binding.append("tx",99,"op","p","o",true);}catch(const std::runtime_error&){rejected=true;}assert(rejected);std::cout<<"CHECKPOINT_EVIDENCE_BINDING_PASS\n";
 {std::ofstream out(ev,std::ios::app|std::ios::binary);out<<"2\ttx\t1\ttorn";}assert(chain.recover_torn_tail());auto records=chain.load();assert(records.size()==1&&records[0].operation=="netlink:set-up");std::cout<<"TORN_EVIDENCE_TAIL_RECOVERY_PASS\n";
 {std::ofstream out(ev,std::ios::app|std::ios::binary);out<<"garbage\n";}bool corrupt=false;try{(void)chain.load(true);}catch(const std::runtime_error&){corrupt=true;}assert(corrupt);std::cout<<"MID_LOG_CORRUPTION_FAIL_CLOSED_PASS\n";fs::remove(cp);fs::remove(ev);}
