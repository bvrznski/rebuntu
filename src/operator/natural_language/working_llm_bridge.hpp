#pragma once
#include <operator/natural_language/contract.hpp>
#include <semantics/working_llm/advisory.hpp>
#include <stdexcept>
#include <string>

namespace rebuntu::operator_ui::natural_language {

struct InterpretedOperatorInput {
    NaturalLanguageContract contract;
    std::string advisory_text;
    bool validated_non_authoritative{false};
};

inline InterpretedOperatorInput from_working_llm(const semantic::working_llm::Advisory& advisory) {
    advisory.validate();
    NaturalLanguageContract c;
    c.stable_id = advisory.request_id;
    c.provenance = "working-llm:" + advisory.model;
    c.evidence.push_back("non-authoritative-advisory");
    for (const auto& assumption : advisory.assumptions) c.evidence.push_back("assumption:" + assumption);
    return {std::move(c), advisory.content, true};
}

} // namespace rebuntu::operator_ui::natural_language
