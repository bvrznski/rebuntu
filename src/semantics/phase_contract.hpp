#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantic {

struct EvidenceRef {
    std::string source;
    std::string native_authority;
    std::string observation_id;
};

struct SemanticDecision {
    enum class Disposition { observe, propose, authorize, reconcile, escalate };
    Disposition disposition{Disposition::observe};
    std::string rationale;
    std::vector<EvidenceRef> evidence;
};

struct NativeOperation {
    std::string provider;
    std::string operation;
    std::vector<std::string> arguments;
};

// Semantic phase contracts never own Linux mechanism state. NativeOperation is
// only a typed request to a narrow provider; verification must re-observe the
// authoritative native mechanism afterwards.
class PhaseSemanticContract {
public:
    virtual ~PhaseSemanticContract() = default;
    [[nodiscard]] virtual std::string_view capability_name() const noexcept = 0;
    [[nodiscard]] virtual SemanticDecision assess() const = 0;
    [[nodiscard]] virtual std::optional<NativeOperation> propose_native_operation() const = 0;
};

} // namespace rebuntu::semantic
