// rebuntu::interfaces::state_provider — State provider contracts (Phase 0.16)
//
// This header establishes Rebuntu's typed interface for state observation
// providers. It defines what a state provider MUST implement, without dictating
// HOW it observes state.
//
// Architecture:
//   Interfaces (what)        -> src/interfaces/
//   Adapters/Providers (how) -> src/adapters/systemd/, src/adapters/procfs/, etc.

#pragma once

#include <system/runtime/contracts.hpp>
#include <string>
#include <vector>
#include <optional>
#include <chrono>

namespace rebuntu::interfaces {

struct StateProviderId {
    std::string value;
    
    explicit StateProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const StateProviderId& a, const StateProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const StateProviderId& a, const StateProviderId& b) {
    return !(a == b);
}

struct StateObservation {
    std::string entity_id;
    
    StateProviderId provider_id;
    
    std::chrono::system_clock::time_point observed_at;
    
    rebuntu::runtime::LifecycleState lifecycle;
    rebuntu::runtime::WorkState work;
    rebuntu::runtime::ControlState control;
    rebuntu::runtime::ReadinessState readiness;
    rebuntu::runtime::HealthState health;
    rebuntu::runtime::RecoveryState recovery;
    
    std::optional<std::string> native_state_name;
    std::optional<int64_t> pid;
    std::optional<std::string> description;
};

struct StateProviderResult {
    bool success = false;
    
    std::vector<StateObservation> observations;
    
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
};

class StateProvider {
public:
    virtual ~StateProvider() = default;
    
    virtual StateObservation observe(const std::string& entity_id) = 0;
    
    virtual StateProviderId provider_id() const = 0;
};

class CompositeStateProvider : public StateProvider {
public:
    virtual ~CompositeStateProvider() = default;
    
    virtual void add_provider(std::unique_ptr<StateProvider> provider) = 0;
    
    virtual std::vector<std::unique_ptr<StateProvider>> providers() const = 0;
};

class StateProviderSelector {
public:
    virtual ~StateProviderSelector() = default;
    
    virtual std::optional<StateProviderId> select(
        const std::string& entity_id,
        const std::optional<std::vector<std::string>>& hint_providers = std::nullopt
    ) = 0;
    
    virtual std::vector<StateProviderId> list_available() const = 0;
};

enum class StateProviderCapability {
    SUBSCRIPTION,
    BULK_OBSERVATION,
    METADATA_QUERY,
};

}  // namespace rebuntu::interfaces

namespace std {
template <> struct hash<rebuntu::interfaces::StateProviderId> {
    size_t operator()(const rebuntu::interfaces::StateProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
