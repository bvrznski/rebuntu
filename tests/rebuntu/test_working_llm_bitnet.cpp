#include <semantics/working_llm/endpoint.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace rebuntu::semantic::working_llm;
int main() {
    auto e = default_bitnet_falcon10b();
    if (e.model != "Falcon3-10B-Instruct-1.58bit" || e.chat_url() != "http://127.0.0.1:8082/v1/chat/completions" || e.authoritative) return 1;
    auto request = chat_request("hello \"rebuntu\"", 0.1, 64);
    if (request.find("hello \\\"rebuntu\\\"") == std::string::npos) return 2;
    bool rejected = false;
    try { auto bad=e; bad.authoritative=true; bad.validate(); } catch (const std::invalid_argument&) { rejected=true; }
    if (!rejected) return 3;
    std::cout << "WORKING_LLM_BITNET_FALCON10B_PASS\n";
    return 0;
}
