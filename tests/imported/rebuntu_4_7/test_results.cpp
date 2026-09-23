// Unit tests for rebuntu::core::results (Phase 0.17)

#include <system/core/contracts.hpp>
#include <system/core/results.hpp>

#include <iostream>
#include <string>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)
}

int main() {
    using rebuntu::core::VerificationStatus;
    using rebuntu::core::FailureClassification;
    using rebuntu::core::EvidenceRetention;
    using rebuntu::core::SecretRedactionPolicy;
    using rebuntu::core::to_string;

    CHECK(to_string(VerificationStatus::kVerified) == "verified");
    CHECK(to_string(VerificationStatus::kNotVerified) == "not_verified");
    CHECK(to_string(VerificationStatus::kVerificationFailed) == "verification_failed");
    CHECK(to_string(VerificationStatus::kUnknown) == "unknown");

    CHECK(to_string(FailureClassification::kExecution) == "execution_failure");
    CHECK(to_string(FailureClassification::kVerification) == "verification_failure");
    CHECK(to_string(FailureClassification::kValidation) == "validation_failure");
    CHECK(to_string(FailureClassification::kAuthorization) == "authorization_failure");
    CHECK(to_string(FailureClassification::kResource) == "resource_failure");
    CHECK(to_string(FailureClassification::kTimeout) == "timeout_failure");
    CHECK(to_string(FailureClassification::kCancelled) == "cancelled_failure");
    CHECK(to_string(FailureClassification::kUnknown) == "unknown_failure");

    CHECK(to_string(EvidenceRetention::kNone) == "none");
    CHECK(to_string(EvidenceRetention::kBrief) == "brief");
    CHECK(to_string(EvidenceRetention::kStandard) == "standard");
    CHECK(to_string(EvidenceRetention::kLong) == "long");
    CHECK(to_string(EvidenceRetention::kPermanent) == "permanent");

    CHECK(to_string(SecretRedactionPolicy::kStrict) == "strict");
    CHECK(to_string(SecretRedactionPolicy::kRedact) == "redact");
    CHECK(to_string(SecretRedactionPolicy::kTrustBoundary) == "trust_boundary");

    auto vr1 = rebuntu::core::VerificationResult::verified();
    CHECK(vr1.status == VerificationStatus::kVerified);

    auto er1 = rebuntu::core::ExecutionResult<int>::success(42);
    CHECK(er1.succeeded());
    CHECK(*er1.value == 42);

    auto erv1 = rebuntu::core::ExecutionResult<void>::success();
    CHECK(erv1.succeeded());

    auto agg1 = rebuntu::core::RetryAggregation{};
    agg1.final_outcome = rebuntu::core::SemanticStatus::kSuccess;
    CHECK(agg1.succeeded());
    CHECK(agg1.total_attempts() == 0);

    std::cout << "test_results: ";
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "OK\n";
    return 0;
}
