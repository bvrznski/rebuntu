#include <semantics/working_llm/session.hpp>
#include <iostream>
#include <stdexcept>
using namespace rebuntu::semantic::working_llm;
int main() {
    Session s;
    auto r=s.prepare("explain why nginx is not converged", 7);
    if (r.request_id!="working-llm-7" || r.url.find("127.0.0.1:8082")==std::string::npos) return 1;
    if (r.body.find("non-authoritative") == std::string::npos || r.body.find("Request-ID: working-llm-7") == std::string::npos) return 2;
    auto a=s.accept(r.request_id,"proposed interpretation only");
    if (a.authoritative || a.model!="Falcon3-10B-Instruct-1.58bit") return 3;
    std::cout << "WORKING_LLM_GUARDED_SESSION_PASS\n";

    RequestBudget b; b.max_prompt_bytes=4;
    Session bounded(default_bitnet_falcon10b(), b);
    bool rejected=false; try { (void)bounded.prepare("12345",1); } catch(const std::invalid_argument&) { rejected=true; }
    if(!rejected) return 4;
    std::cout << "WORKING_LLM_BUDGET_FAIL_CLOSED_PASS\n";

    Session failing;
    failing.transport_failure(); failing.transport_failure(); failing.transport_failure();
    if(failing.available()) return 5;
    bool open=false; try { (void)failing.prepare("hello",2); } catch(const std::runtime_error&) { open=true; }
    if(!open) return 6;
    std::cout << "WORKING_LLM_CIRCUIT_BREAKER_PASS\n";

    Advisory bad; bad.request_id="x"; bad.model="m"; bad.content="x"; bad.requests_native_execution=true;
    rejected=false; try { bad.validate(); } catch(const std::invalid_argument&) { rejected=true; }
    if(!rejected) return 7;
    std::cout << "WORKING_LLM_NATIVE_EXECUTION_REJECTED_PASS\n";
}
