// rebuntu::events::activation — Native Event Activation Engine (Phase 4.16)
//
// This module establishes the contracts and interfaces for activating Rebuntu
// work from native Linux events without polling-first architecture.
//
// Event-to-Activation Flow:
//   EVENT -> normalized Event/Fact -> trigger match -> Activation -> typed work request

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <tuple>
#include <mutex>

namespace rebuntu::events {

struct ActivationId {
    std::string value;
    explicit operator std::string() const { return value; }
};

inline bool operator==(const ActivationId& a, const ActivationId& b) {
    return a.value == b.value;
}

inline bool operator!=(const ActivationId& a, const ActivationId& b) {
    return !(a == b);
}

struct ActivationRecord {
    ActivationId id;
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> triggered_at;
    
    std::string source_event_id;
    std::string source_type;
    
    std::string trigger_id;
    runtime::Condition triggered_condition;
    
    std::optional<std::string> target_kind;
    std::optional<std::string> target_id;
    
    std::optional<std::string> authorized_by;
    std::optional<std::string> deduplication_key;
};

enum class ActivationDecision {
    kAllow,
    kSuppress,
    kCoalesce,
    kDefer,
    kReject
};

inline std::string to_string(ActivationDecision d) {
    switch (d) {
        case ActivationDecision::kAllow:     return "allow";
        case ActivationDecision::kSuppress:  return "suppress";
        case ActivationDecision::kCoalesce:  return "coalesce";
        case ActivationDecision::kDefer:     return "defer";
        case ActivationDecision::kReject:    return "reject";
        default:                             return "unknown";
    }
}

struct TriggerDefinition {
    std::string id;
    
    std::optional<std::chrono::system_clock::time_point> activation_start;
    std::optional<std::chrono::system_clock::time_point> activation_end;
    
    std::optional<std::string> source_filter;
    std::optional<std::string> type_filter;
    
    runtime::Condition condition;
    
    std::optional<std::string> target_kind;
    std::optional<std::string> target_id;
    
    bool suppress_while_running = true;
    std::optional<std::chrono::milliseconds> cooldown_after_activation;
    
    std::optional<std::string> authorization_scope;
    
    bool enabled = true;
};

class TriggerRegistry {
public:
    void register_trigger(TriggerDefinition def);
    void unregister_trigger(const std::string& id);
    void set_enabled(const std::string& id, bool enabled);
    
    std::vector<TriggerDefinition> find_matching_triggers(
        const runtime::Event& event) const;
    
    std::optional<TriggerDefinition> find(const std::string& id) const;
    std::vector<TriggerDefinition> list(bool only_enabled = true) const;

private:
    std::unordered_map<std::string, TriggerDefinition> triggers_;
};

class DeduplicationCache {
public:
    explicit DeduplicationCache(std::chrono::milliseconds window = std::chrono::seconds(5));
    
    bool is_duplicate(const std::string& dedup_key);
    void record_activation(const std::string& dedup_key);
    void cleanup(std::chrono::system_clock::time_point now);

private:
    std::chrono::milliseconds window_;
    std::unordered_map<std::string, std::chrono::system_clock::time_point> activations_;
};

struct ActivationAuthorization {
    bool authorized;
    core::Error error;
    bool has_error = false;
    
    static ActivationAuthorization allow() { 
        ActivationAuthorization a; 
        a.authorized = true; 
        return a; 
    }
    static ActivationAuthorization reject(const core::Error& err) { 
        ActivationAuthorization a; 
        a.authorized = false;
        a.error = err;
        a.has_error = true;
        return a; 
    }
};

class EventMatcher {
public:
    std::tuple<std::optional<runtime::Condition>, ActivationDecision, core::Error>
    match(const TriggerDefinition& trigger, const runtime::Event& event) const;

private:
    bool matches_source_filter(
        const std::string& event_source,
        const std::optional<std::string>& filter) const;
    
    bool matches_type_filter(
        const std::string& event_type,
        const std::optional<std::string>& filter) const;
    
    bool evaluate_condition(const runtime::Condition& cond) const;
};

struct ActivationResult {
    ActivationDecision decision;
    std::optional<ActivationRecord> activation;
    std::vector<core::Evidence> evidence;
};

class ActivationEngine {
public:
    explicit ActivationEngine(
        std::unique_ptr<TriggerRegistry> registry,
        std::unique_ptr<DeduplicationCache> dedup_cache,
        std::unique_ptr<EventMatcher> matcher);
    
    virtual ~ActivationEngine() = default;
    
    ActivationResult process_event(const runtime::Event& event);
    
    std::vector<ActivationResult> process_events(
        const std::vector<runtime::Event>& events,
        size_t max_batch_size = 1000);
    
    size_t active_activations() const;
    
    struct Metrics {
        size_t events_processed = 0;
        size_t activations_created = 0;
        size_t activations_suppressed = 0;
        size_t activations_coalesced = 0;
        size_t activations_rejected = 0;
    };
    Metrics metrics() const;

private:
    std::unique_ptr<TriggerRegistry> registry_;
    std::unique_ptr<DeduplicationCache> dedup_cache_;
    std::unique_ptr<EventMatcher> matcher_;
    
    mutable std::mutex active_lock_;
    size_t active_count_ = 0;
    
    Metrics metrics_;
    mutable std::mutex metrics_lock_;
};

inline std::unique_ptr<TriggerRegistry> make_trigger_registry() {
    return std::make_unique<TriggerRegistry>();
}

inline std::unique_ptr<DeduplicationCache> make_deduplication_cache(
        std::chrono::milliseconds window = std::chrono::seconds(5)) {
    return std::make_unique<DeduplicationCache>(window);
}

inline std::unique_ptr<EventMatcher> make_event_matcher() {
    return std::make_unique<EventMatcher>();
}

inline std::unique_ptr<ActivationEngine> make_activation_engine(
        std::unique_ptr<TriggerRegistry> registry = nullptr,
        std::chrono::milliseconds dedup_window = std::chrono::seconds(5)) {
    if (!registry) {
        registry = make_trigger_registry();
    }
    
    return std::make_unique<ActivationEngine>(
        std::move(registry),
        make_deduplication_cache(dedup_window),
        make_event_matcher());
}

}  // namespace rebuntu::events

namespace std {
template <> struct hash<rebuntu::events::ActivationId> {
    size_t operator()(const rebuntu::events::ActivationId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}