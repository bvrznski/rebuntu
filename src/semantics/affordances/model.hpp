#pragma once
#include <chrono>
#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::semantics::affordances {
enum class Truth { yes, no, unknown };
enum class CapabilityState { available, degraded, unavailable, unknown };
enum class BlockerKind { missing_requirement, stale_evidence, conflicting_evidence, resource_contention, policy, security, prerequisite, provider_failure, target_mismatch, deadline };

struct Evidence {
    std::string source;
    std::string authority;
    std::string key;
    std::string value;
    std::uint64_t generation{0};
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::seconds ttl{0};
    bool trusted{false};
    bool fresh(std::chrono::system_clock::time_point now) const noexcept { return ttl.count() > 0 && observed_at + ttl >= now; }
};
struct Requirement { std::string key; std::string expected; bool mandatory{true}; };
struct Prerequisite { std::string capability_id; std::vector<std::string> alternatives; };
struct CapabilityDefinition {
    std::string id;
    std::string provider;
    std::set<std::string> verbs;
    std::vector<Requirement> requirements;
    std::vector<Prerequisite> prerequisites;
    std::set<std::string> target_kinds;
};
struct CapabilityInstance {
    CapabilityDefinition definition;
    std::string target_id;
    CapabilityState state{CapabilityState::unknown};
    std::vector<Evidence> evidence;
};
struct EvaluationContext {
    std::string target_id;
    std::string target_kind;
    std::string verb;
    std::map<std::string,std::string> facts;
    std::set<std::string> available_capabilities;
    std::set<std::string> authorized_verbs; // policy result supplied by security, never inferred here
    std::uint64_t observation_generation{0};
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};
};
struct Blocker { BlockerKind kind; std::string subject; std::string detail; };
struct AffordanceResult {
    Truth feasible{Truth::unknown};
    Truth ready{Truth::unknown};
    bool authorized{false};
    bool stale{false};
    std::uint64_t evaluated_generation{0};
    std::vector<Blocker> blockers;
    std::vector<Evidence> evidence;
    bool executable() const noexcept { return feasible==Truth::yes && ready==Truth::yes && authorized && !stale && blockers.empty(); }
};
}
