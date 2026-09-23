#include <operator/natural_language/working_llm_bridge.hpp>
#include <iostream>
using namespace rebuntu::semantic::working_llm;
int main(){
 Advisory a; a.request_id="working-llm-9"; a.model="Falcon3-10B-Instruct-1.58bit"; a.content="intent proposal"; a.assumptions={"service name refers to system unit"};
 auto x=rebuntu::operator_ui::natural_language::from_working_llm(a);
 if(!x.validated_non_authoritative || x.contract.stable_id!=a.request_id || x.contract.evidence.size()!=2) return 1;
 std::cout<<"WORKING_LLM_OPERATOR_PROVENANCE_BRIDGE_PASS\n";
}
