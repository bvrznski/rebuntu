#pragma once

#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <system/core/contracts.hpp>

namespace rebuntu::evidence {

// ============================================================================
// ObservationIdentity — Stable identity for an observation
// ============================================================================

struct ObservationIdentity {
    std::string domain;
    std::string source;
    std::string key;
    
    static ObservationIdentity make(std::string domain, std::string source, std::string key) {
        return {std::move(domain), std::move(source), std::move(key)};
    }
    
    bool operator==(const ObservationIdentity& other) const noexcept;
};

inline size_t hash_identity(const ObservationIdentity& id) noexcept {
    size_t h1 = std::hash<std::string>{}(id.domain);
    size_t h2 = std::hash<std::string>{}(id.source);
    size_t h3 = std::hash<std::string>{}(id.key);
    return h1 ^ (h2 << 1) ^ (h3 << 2);
}

// ============================================================================
// ObservationProvenance — Where observation came from and how fresh
// ============================================================================

struct ObservationProvenance {
    std::string provider;
    core::SemanticStatus acquisition_status = core::SemanticStatus::kSuccess;
    
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::chrono::system_clock::time_point> first_observed_at;
    std::optional<std::chrono::system_clock::time_point> last_seen_at;
};

// ============================================================================
// DeduplicationKey — Key for finding equivalent observations
// ============================================================================

struct DeduplicationKey {
    std::string semantic_domain;   // Semantic domain (e.g., "system.memory.total")
    std::optional<std::string> subject_id;  // Subject if applicable
    
    static DeduplicationKey make(std::string semantic_domain,
                                  std::optional<std::string> subject_id = {});
    
    bool operator==(const DeduplicationKey& other) const noexcept;
};

inline size_t hash_dedup_key(const DeduplicationKey& key) noexcept {
    size_t h1 = std::hash<std::string>{}(key.semantic_domain);
    size_t h2 = key.subject_id.has_value() ? std::hash<std::string>{}(*key.subject_id) : 0;
    return h1 ^ (h2 << 1);
}

// ============================================================================
// ObservationRecord — Evidence with identity and provenance tracking
// ============================================================================

struct ObservationRecord {
    core::Evidence evidence;                    // The actual evidence value
    
    ObservationIdentity identity;              // Stable identity for deduplication
    DeduplicationKey dedupe_key;               // Key for semantic equivalence grouping
    ObservationProvenance provenance;
    
    size_t occurrence_count = 1;               // How many times this was observed
    std::chrono::system_clock::time_point first_seen_at;
    std::optional<std::chrono::system_clock::time_point> last_occurrence_at;
    
    std::vector<ObservationIdentity> source_aliases;  // Alternative identities for same observation
};

// ============================================================================
// DeduplicationConfig — Configuration for deduplication behavior
// ============================================================================

struct DeduplicationConfig {
    std::chrono::milliseconds window{std::chrono::minutes(5)};
    size_t max_occurrences_per_identity = 1000;
    bool preserve_source_differences = true;
    bool deduplicate_identical_values = true;
};

// ============================================================================
// DeduplicationResult — Result of attempting to add an observation
// ============================================================================

struct DeduplicationResult {
    enum class Action {
        kNew,              // Observation was new and added
        kUpdated,          // Existing observation updated (new occurrence)
        kDuplicate,        // Exact duplicate within window (not counted)
        kPreservedSource,  // Different source preserved as additional evidence
    };
    
    Action action = Action::kNew;
    std::optional<size_t> existing_occurrence_count;  // Count before this addition
    
    ObservationIdentity identity_added;
    DeduplicationKey dedupe_key_used;
};

// ============================================================================
// Hash and equality functors for unordered_map (defined BEFORE ObservationDeduplicator)
// ============================================================================

struct IdentityHash {
    size_t operator()(const ObservationIdentity& id) const noexcept {
        return hash_identity(id);
    }
};

struct EqualityHash {
    bool operator()(const ObservationIdentity& a, const ObservationIdentity& b) const noexcept {
        return a == b;
    }
};

struct DedupKeyHash {
    size_t operator()(const DeduplicationKey& key) const noexcept {
        return hash_dedup_key(key);
    }
};

struct DedupKeyEquality {
    bool operator()(const DeduplicationKey& a, const DeduplicationKey& b) const noexcept {
        return a == b;
    }
};

// ============================================================================
// ObservationDeduplicator — Manages observation deduplication
// ============================================================================

class ObservationDeduplicator {
public:
    explicit ObservationDeduplicator(DeduplicationConfig config = {});
    
    DeduplicationResult add(const core::Evidence& evidence,
                           const ObservationProvenance& provenance);
    
    std::optional<DeduplicationKey> would_be_duplicate(
        const core::Evidence& evidence,
        std::chrono::system_clock::time_point now) const;
    
    std::vector<ObservationRecord> get_by_identity(const ObservationIdentity& id) const;
    
    std::vector<std::vector<ObservationRecord>> get_equivalent_observations(
        const DeduplicationKey& key) const;
    
    void clear();
    
    void cleanup(std::chrono::system_clock::time_point now);
    
    struct Metrics {
        size_t observations_added = 0;
        size_t duplicates_detected = 0;
        size_t preserved_sources = 0;
        size_t identities_tracked = 0;
        size_t dedup_keys_tracked = 0;
    };
    Metrics metrics() const;

private:
    DeduplicationConfig config_;
    
    std::unordered_map<ObservationIdentity, ObservationRecord, IdentityHash, EqualityHash> records_by_identity_;
    std::unordered_map<DeduplicationKey, std::vector<ObservationIdentity>, DedupKeyHash, DedupKeyEquality> dedupe_index_;
    Metrics metrics_;
};

std::unique_ptr<ObservationDeduplicator> make_observation_deduplicator(
    DeduplicationConfig config = {});

}  // namespace rebuntu::evidence