// rebuntu::system::observation::state_normalizer — State Normalization Implementation (Phase 7.3)
//
// This module implements canonical state normalization for Rebuntu:
//   - Registry for normalizers per domain/provider
//   - Default normalizers for common domains (process, service, filesystem)
//   - Preserves evidence and handles provider-specific values

#include "system/observation/state_normalizer.hpp"

#include <algorithm>
#include <unordered_set>
#include <string>

namespace rebuntu::system::observation {

// ============================================================================
// StateNormalizerRegistryImpl — Concrete implementation of StateNormalizerRegistry
// ============================================================================

class StateNormalizerRegistryImpl : public StateNormalizerRegistry {
public:
    StateNormalizerRegistryImpl() = default;
    ~StateNormalizerRegistryImpl() override = default;
    
    core::Outcome register_normalizer(
        ObservationDomain domain,
        std::string provider_name,
        std::unique_ptr<StateNormalizer> normalizer
    ) override {
        // Check if we already have a normalizer for this combination
        std::string key = to_string(domain) + ":" + provider_name;
        if (registry_.find(key) != registry_.end()) {
            return core::Outcome::failure(
                "E_DUPLICATE_NORMALIZER",
                "Normalizer already registered for domain=" + to_string(domain) +
                ", provider=" + provider_name
            );
        }
        
        registry_[key] = std::move(normalizer);
        domain_order_[domain].push_back(provider_name);
        
        return core::Outcome::success();
    }
    
    StateNormalizer* get_normalizer(
        ObservationDomain domain,
        const std::string& provider_name
    ) const override {
        std::string key = to_string(domain) + ":" + provider_name;
        auto it = registry_.find(key);
        if (it != registry_.end()) {
            return it->second.get();
        }
        
        // Try to find any normalizer for this domain as fallback
        auto domain_it = domain_order_.find(domain);
        if (domain_it != domain_order_.end() && !domain_it->second.empty()) {
            key = to_string(domain) + ":" + domain_it->second.front();
            it = registry_.find(key);
            if (it != registry_.end()) {
                return it->second.get();
            }
        }
        
        return nullptr;
    }
    
    NormalizationResult try_normalize(
        const Observation& observation,
        std::chrono::milliseconds timeout
    ) override {
        // Find the appropriate normalizer for this observation's domain and source
        StateNormalizer* normalizer = get_normalizer(observation.subject.domain, observation.source);
        
        if (!normalizer) {
            return NormalizationResult::unknown(
                "No normalizer registered for domain=" + to_string(observation.subject.domain) +
                ", source=" + observation.source
            );
        }
        
        // Perform normalization with timeout support
        auto start_time = std::chrono::steady_clock::now();
        
        if (observation.error.has_value()) {
            return NormalizationResult::validation_failure(
                observation.raw_value.value_or(""),
                "Observation contains error: " + observation.error->message,
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time)
            );
        }
        
        auto result = normalizer->normalize(observation, timeout);
        
        // Add the original observation to evidence chain
        ObservationIdentity obs_id;
        obs_id.domain_id = observation.subject.domain_id;
        obs_id.domain = observation.subject.domain;
        result.evidence_chain.push_back(obs_id);
        
        return result;
    }
    
    std::vector<std::string> get_normalizer_names(ObservationDomain domain) const override {
        auto it = domain_order_.find(domain);
        if (it != domain_order_.end()) {
            return it->second;
        }
        return {};
    }
    
private:
    static std::string make_key(ObservationDomain domain, const std::string& provider_name) {
        return to_string(domain) + ":" + provider_name;
    }
    
    // Mapping: key = "domain:provider", value = normalizer unique_ptr
    mutable std::unordered_map<std::string, std::unique_ptr<StateNormalizer>> registry_;
    
    // Tracking of registered providers per domain (for fallback selection)
    std::unordered_map<ObservationDomain, std::vector<std::string>> domain_order_;
};

// ============================================================================
// StateNormalizer implementations for specific domains
// ============================================================================

// ProcessStateNormalizer — Normalizes process state values to canonical forms
class ProcessStateNormalizer : public StateNormalizer {
public:
    ProcessStateNormalizer() = default;
    
    NormalizationResult normalize(
        const Observation& observation,
        std::chrono::milliseconds timeout
    ) override {
        auto start_time = std::chrono::steady_clock::now();
        
        (void)timeout;  // Not implemented for now - could add timeout checking
        
        if (!observation.raw_value.has_value()) {
            return NormalizationResult::unknown("No raw value to normalize", elapsed(start_time));
        }
        
        std::string raw = *observation.raw_value;
        std::string canonical;
        
        // Normalize various process state representations to canonical forms
        // These come from /proc/[pid]/stat's 3rd field (state character)
        
        if (raw == "R" || raw == "running" || raw == "runnable") {
            canonical = "running";
        } else if (raw == "S" || raw == "sleeping" || raw == "interruptible_sleep") {
            canonical = "sleeping";
        } else if (raw == "D" || raw == "disk_sleep" || raw == "uninterruptible_sleep" || 
                   raw == "waiting" || raw == "waking") {
            canonical = "disk-sleep";
        } else if (raw == "Z" || raw == "zombie" || raw == "defunct") {
            canonical = "zombie";
        } else if (raw == "T" || raw == "stopped" || raw == "stop" || raw == "tracing_stop") {
            canonical = "stopped";
        } else if (raw == "X" || raw == "dead" || raw == "exit_death") {
            canonical = "dead";
        } else if (raw == "W" || raw == "wakekill") {
            canonical = "wakekill";
        } else if (raw == "P" || raw == "parked") {
            canonical = "parked";
        } else if (raw == "I" || raw == "idle" || raw == "kernel_thread") {
            canonical = "idle";
        } else if (raw == "t" || raw == "tracing_stop") {
            canonical = "tracing-stop";
        } else {
            // Unknown state - preserve the original value
            return NormalizationResult::provider_specific(
                std::move(raw),
                observation.source,
                elapsed(start_time)
            );
        }
        
        return NormalizationResult::success(
            std::move(canonical),
            std::move(raw),
            elapsed(start_time)
        );
    }
    
    bool can_normalize(ObservationDomain domain, const std::string& value) const override {
        if (domain != ObservationDomain::kProcess) return false;
        
        static const std::unordered_set<std::string> kKnownValues = {
            "R", "S", "D", "Z", "T", "t", "X", "W", "P", "I",
            "running", "sleeping", "disk-sleep", "zombie", "stopped",
            "dead", "wakekill", "parked", "idle"
        };
        
        return kKnownValues.find(value) != kKnownValues.end();
    }
    
    std::set<std::string> get_canonical_values() const override {
        return {"running", "sleeping", "disk-sleep", "zombie", 
                "stopped", "tracing-stop", "dead", "wakekill", "parked", "idle"};
    }
    
    std::unordered_map<std::string, std::string> normalization_rules() const override {
        return {
            {"source", "/proc/[pid]/stat (field 3: process state)"},
            {"mapping", "state_character -> canonical_state_name"},
            {"fallback", "provider_specific"}
        };
    }
    
private:
    static std::chrono::milliseconds elapsed(std::chrono::steady_clock::time_point start) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
    }
};

// ServiceStateNormalizer — Normalizes systemd service state values
class ServiceStateNormalizer : public StateNormalizer {
public:
    ServiceStateNormalizer() = default;
    
    NormalizationResult normalize(
        const Observation& observation,
        std::chrono::milliseconds timeout
    ) override {
        auto start_time = std::chrono::steady_clock::now();
        
        (void)timeout;  // Not implemented for now
        
        if (!observation.raw_value.has_value()) {
            return NormalizationResult::unknown("No raw value to normalize", elapsed(start_time));
        }
        
        std::string raw = *observation.raw_value;
        std::string canonical;
        
        // Normalize systemd service active states
        // These come from systemctl's ActiveState and SubState properties
        
        if (raw == "active" || raw == "running" || raw == "activated") {
            canonical = "active";
        } else if (raw == "inactive" || raw == "dead" || raw == "stopped") {
            canonical = "inactive";
        } else if (raw == "activating" || raw == "start" || raw == "starting") {
            canonical = "activating";
        } else if (raw == "deactivating" || raw == "stop" || raw == "stopping") {
            canonical = "deactivating";
        } else if (raw == "failed" || raw == "error" || raw == "failure") {
            canonical = "failed";
        } else if (raw.empty()) {
            return NormalizationResult::unknown(
                "Empty service state value",
                elapsed(start_time)
            );
        } else {
            // SubState or provider-specific value
            return NormalizationResult::provider_specific(
                std::move(raw),
                observation.source,
                elapsed(start_time)
            );
        }
        
        return NormalizationResult::success(
            std::move(canonical),
            std::move(raw),
            elapsed(start_time)
        );
    }
    
    bool can_normalize(ObservationDomain domain, const std::string& value) const override {
        if (domain != ObservationDomain::kService) return false;
        
        static const std::unordered_set<std::string> known_values = {
            "active", "inactive", "activating", "deactivating", "failed",
            "running", "dead", "stopped", "start", "starting", "stop", "stopping",
            "error", "failure"
        };
        
        return known_values.find(value) != known_values.end();
    }
    
    std::set<std::string> get_canonical_values() const override {
        return {"active", "inactive", "activating", "deactivating", "failed"};
    }
    
    std::unordered_map<std::string, std::string> normalization_rules() const override {
        return {
            {"source", "systemctl show UNIT (ActiveState, SubState)"},
            {"mapping", "service_state -> canonical_state_name"},
            {"fallback", "provider_specific"}
        };
    }
    
private:
    static std::chrono::milliseconds elapsed(std::chrono::steady_clock::time_point start) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
    }
};

// ServiceUnitStateNormalizer — Normalizes systemd unit file state values
class ServiceUnitStateNormalizer : public StateNormalizer {
public:
    ServiceUnitStateNormalizer() = default;
    
    NormalizationResult normalize(
        const Observation& observation,
        std::chrono::milliseconds timeout
    ) override {
        auto start_time = std::chrono::steady_clock::now();
        
        (void)timeout;  // Not implemented for now
        
        if (!observation.raw_value.has_value()) {
            return NormalizationResult::unknown("No raw value to normalize", elapsed(start_time));
        }
        
        std::string raw = *observation.raw_value;
        std::string canonical;
        
        // Normalize systemd unit file states
        // These come from systemctl's UnitFileState property
        
        if (raw == "enabled" || raw == "enabled-runtime") {
            canonical = "enabled";
        } else if (raw == "disabled" || raw == "static" || raw == "indirect") {
            canonical = "disabled";
        } else if (raw == "masked" || raw == "masked-runtime") {
            canonical = "masked";
        } else if (raw.empty()) {
            return NormalizationResult::unknown(
                "Empty unit file state value",
                elapsed(start_time)
            );
        } else {
            // Provider-specific value
            return NormalizationResult::provider_specific(
                std::move(raw),
                observation.source,
                elapsed(start_time)
            );
        }
        
        return NormalizationResult::success(
            std::move(canonical),
            std::move(raw),
            elapsed(start_time)
        );
    }
    
    bool can_normalize(ObservationDomain domain, const std::string& value) const override {
        if (domain != ObservationDomain::kService) return false;
        
        static const std::unordered_set<std::string> known_values = {
            "enabled", "disabled", "masked", "static", "indirect",
            "enabled-runtime", "masked-runtime"
        };
        
        return known_values.find(value) != known_values.end();
    }
    
    std::set<std::string> get_canonical_values() const override {
        return {"enabled", "disabled", "masked"};
    }
    
    std::unordered_map<std::string, std::string> normalization_rules() const override {
        return {
            {"source", "systemctl show UNIT (UnitFileState)"},
            {"mapping", "unit_file_state -> canonical_state_name"},
            {"fallback", "provider_specific"}
        };
    }
    
private:
    static std::chrono::milliseconds elapsed(std::chrono::steady_clock::time_point start) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
    }
};

// Factory function
std::unique_ptr<StateNormalizerRegistry> make_state_normalizer_registry() {
    auto registry = std::make_unique<StateNormalizerRegistryImpl>();
    
    // Register default normalizers for each domain
    registry->register_normalizer(
        ObservationDomain::kProcess,
        "procfs",
        std::make_unique<ProcessStateNormalizer>()
    );
    
    registry->register_normalizer(
        ObservationDomain::kService,
        "systemd",
        std::make_unique<ServiceStateNormalizer>()
    );
    
    registry->register_normalizer(
        ObservationDomain::kService,
        "systemd",
        std::make_unique<ServiceUnitStateNormalizer>()
    );
    
    return registry;
}

}  // namespace rebuntu::system::observation