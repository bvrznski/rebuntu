// rebuntu::evidence::deduplication — Observation Deduplication System (Phase 5.41)
//
// This module implements typed observation deduplication that:
//   - Preserves meaningful repeated evidence from different sources
//   - Uses identity and provenance to drive deduplication decisions
//   - Avoids erasing source differences between equivalent observations

#include <system/evidence/deduplication.hpp>

namespace rebuntu::evidence {

ObservationDeduplicator::ObservationDeduplicator(DeduplicationConfig config)
    : config_(config) {}

DeduplicationResult ObservationDeduplicator::add(const core::Evidence& evidence,
                                                const ObservationProvenance& provenance) {
    metrics_.observations_added++;
    
    // Determine identity from the evidence's source
    auto identity = ObservationIdentity::make(
        "evidence",                    // domain: where it came from (semantic category)
        evidence.source,               // source: specific mechanism (procfs, systemd, etc.)
        evidence.value);               // key: what was observed
    
    auto dedupe_key = DeduplicationKey::make(evidence.source);
    
    // Check if this is an exact duplicate within the window
    auto existing_it = records_by_identity_.find(identity);
    if (existing_it != records_by_identity_.end()) {
        auto& record = existing_it->second;
        
        // Check time window
        auto now = provenance.observed_at;
        auto window_start = now - config_.window;
        
        bool within_window = record.first_seen_at >= window_start;
        
        if (within_window && config_.deduplicate_identical_values) {
            // Check if values are identical
            if (record.evidence.value == evidence.value) {
                metrics_.duplicates_detected++;
                return {DeduplicationResult::Action::kDuplicate, 
                        record.occurrence_count, identity, dedupe_key};
            }
        }
        
        // Update existing record
        record.occurrence_count++;
        record.last_occurrence_at = now;
        record.provenance.last_seen_at = now;
        
        if (config_.preserve_source_differences && record.evidence.value != evidence.value) {
            metrics_.preserved_sources++;
        }
        
        return {DeduplicationResult::Action::kUpdated, 
                record.occurrence_count - 1, identity, dedupe_key};
    }
    
    // Create new record
    ObservationRecord record;
    record.evidence = evidence;
    record.identity = identity;
    record.dedupe_key = dedupe_key;
    record.provenance = provenance;
    record.first_seen_at = provenance.observed_at;
    record.occurrence_count = 1;
    
    records_by_identity_[identity] = record;
    
    // Update dedup key index
    dedupe_index_[dedupe_key].push_back(identity);
    
    metrics_.identities_tracked = records_by_identity_.size();
    metrics_.dedup_keys_tracked = dedupe_index_.size();
    
    return {DeduplicationResult::Action::kNew, std::nullopt, identity, dedupe_key};
}

std::optional<DeduplicationKey> ObservationDeduplicator::would_be_duplicate(
    const core::Evidence& evidence,
    std::chrono::system_clock::time_point now) const {
    
    auto identity = ObservationIdentity::make("evidence", evidence.source, evidence.value);
    auto dedupe_key = DeduplicationKey::make(evidence.source);
    
    // Check if there's an existing record in the window
    auto it = records_by_identity_.find(identity);
    if (it != records_by_identity_.end()) {
        const auto& record = it->second;
        auto window_start = now - config_.window;
        
        if (record.first_seen_at >= window_start) {
            return dedupe_key;
        }
    }
    
    return std::nullopt;
}

std::vector<ObservationRecord> ObservationDeduplicator::get_by_identity(
    const ObservationIdentity& id) const {
    auto it = records_by_identity_.find(id);
    if (it != records_by_identity_.end()) {
        return {it->second};
    }
    return {};
}

std::vector<std::vector<ObservationRecord>> ObservationDeduplicator::get_equivalent_observations(
    const DeduplicationKey& key) const {
    std::vector<std::vector<ObservationRecord>> result;
    
    auto it = dedupe_index_.find(key);
    if (it != dedupe_index_.end()) {
        for (const auto& identity : it->second) {
            auto record_it = records_by_identity_.find(identity);
            if (record_it != records_by_identity_.end()) {
                result.push_back({record_it->second});
            }
        }
    }
    
    return result;
}

void ObservationDeduplicator::clear() {
    records_by_identity_.clear();
    dedupe_index_.clear();
    metrics_ = Metrics{};  // Reset all metrics to defaults
}

void ObservationDeduplicator::cleanup(std::chrono::system_clock::time_point now) {
    auto window_start = now - config_.window;
    
    for (auto it = records_by_identity_.begin(); it != records_by_identity_.end();) {
        if (it->second.first_seen_at < window_start) {
            // Remove from dedup index
            auto& identities = dedupe_index_[it->second.dedupe_key];
            identities.erase(
                std::remove(identities.begin(), identities.end(), it->first),
                identities.end());
            
            it = records_by_identity_.erase(it);
        } else {
            ++it;
        }
    }
    
    // Clean up empty entries in dedup index
    for (auto it = dedupe_index_.begin(); it != dedupe_index_.end();) {
        if (it->second.empty()) {
            it = dedupe_index_.erase(it);
        } else {
            ++it;
        }
    }
}

ObservationDeduplicator::Metrics ObservationDeduplicator::metrics() const {
    return metrics_;
}

std::unique_ptr<ObservationDeduplicator> make_observation_deduplicator(
    DeduplicationConfig config) {
    return std::make_unique<ObservationDeduplicator>(config);
}

// ============================================================================
// ObservationIdentity equality operator
// ============================================================================

bool ObservationIdentity::operator==(const ObservationIdentity& other) const noexcept {
    return domain == other.domain &&
           source == other.source &&
           key == other.key;
}

// ============================================================================
// DeduplicationKey factory function
// ============================================================================

DeduplicationKey DeduplicationKey::make(std::string semantic_domain,
                                         std::optional<std::string> subject_id) {
    return {std::move(semantic_domain), std::move(subject_id)};
}

// ============================================================================
// DeduplicationKey equality operator
// ============================================================================

bool DeduplicationKey::operator==(const DeduplicationKey& other) const noexcept {
    return semantic_domain == other.semantic_domain &&
           subject_id == other.subject_id;
}

}  // namespace rebuntu::evidence
