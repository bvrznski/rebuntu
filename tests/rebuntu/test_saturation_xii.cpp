#include "domains/common/saturation.hpp"
#include "control/verification/evidence/durable_chain.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace rebuntu; using namespace rebuntu::domains::common;
static security::policy::AuthorizeMutation allow_all=[](const core::NativeOperation&,const security::policy::AuthorizationContext& c){return security::policy::AuthorizationResult{security::policy::Decision::allow,"test",c.plan_fingerprint};};
int main(){
 {DomainProfile p{"network","netlink",{{"mutation",{"attach"},{}}}};std::vector<OperationRuleV2> rules{{"attachment","bridge0","attach","netlink",true,{{"__verify_relationship.member_of","bridge0"}}}};core::Entity state{"eth0","network",{{"attachment","none"}}, {}};std::vector<Relationship> rels;DomainReconciler r(p,rules);ReconcileOptions o;o.authorize=allow_all;o.guard_pre_execution_drift=false;o.guard_each_operation_drift=false;o.transaction_binding="tx-topology-1";o.observe_relationships=[&](const std::string&){return rels;};auto obs=[&](const std::string&)->std::optional<core::Entity>{return state;};auto ex=[&](const core::NativeOperation& op){state.attributes[op.arguments.at("attribute")]=op.arguments.at("desired");rels.push_back({"eth0","member_of","bridge0",{}});return true;};auto out=r.reconcile({"eth0",{{"attachment","bridge0"}},"topology"},obs,ex,{},o);assert(out.converged&&out.operation_evidence.size()==1&&out.operation_evidence[0].passed&&out.operation_evidence[0].transaction_binding=="tx-topology-1");}
 std::cout<<"RELATIONSHIP_POSTCONDITION_PASS\n";
 {DomainProfile p{"network","netlink",{{"mutation",{"attach"},{}}}};std::vector<OperationRuleV2> rules{{"attachment","bridge0","attach","netlink",true,{{"__verify_relationship.member_of","bridge0"}}}};core::Entity state{"eth0","network",{{"attachment","none"}}, {}};DomainReconciler r(p,rules);ReconcileOptions o;o.authorize=allow_all;o.guard_pre_execution_drift=false;o.guard_each_operation_drift=false;auto obs=[&](const std::string&)->std::optional<core::Entity>{return state;};auto ex=[&](const core::NativeOperation& op){state.attributes[op.arguments.at("attribute")]=op.arguments.at("desired");return true;};auto out=r.reconcile({"eth0",{{"attachment","bridge0"}},"topology"},obs,ex,{},o);assert(!out.converged&&!out.operation_evidence.empty()&&!out.operation_evidence.back().passed);}
 std::cout<<"RELATIONSHIP_OBSERVATION_FAIL_CLOSED_PASS\n";
 {namespace ev=control::verification::evidence;auto path=std::filesystem::temp_directory_path()/"rebuntu_evidence_xii.log";std::filesystem::remove(path);ev::DurableEvidenceChain chain(path);chain.append({0,"tx1",0,"op1","state=ready","ready",true,{},{}});chain.append({0,"tx1",1,"op2","health=ok","ok",true,{},{}});auto records=chain.load();assert(records.size()==2&&records[1].previous_digest==records[0].digest);std::ofstream corrupt(path,std::ios::app);corrupt<<"corruption\n";corrupt.close();bool rejected=false;try{(void)chain.load();}catch(const std::runtime_error&){rejected=true;}assert(rejected);std::filesystem::remove(path);}
 std::cout<<"DURABLE_EVIDENCE_CHAIN_PASS\n";
}
