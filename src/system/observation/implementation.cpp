// rebuntu::system::observation — Observation Architecture Implementation (Phase 7.0)
//
// This module provides implementations for the observation architecture interfaces

#include "system/observation/types.hpp"
#include "adapters/procfs/process/types.hpp"
#include "adapters/systemd/service/types.hpp"

namespace rebuntu::system::observation {

// ============================================================================
// SnapshotBuilder Implementation
// ============================================================================

class SnapshotBuilderImpl : public SnapshotBuilder {
public:
    ~SnapshotBuilderImpl() override = default;
    
    core::Outcome start(const std::string& id) override {
        snapshot_ = Snapshot::make(id);
        snapshot_.state = SnapshotState::kUnknown;
        return core::Outcome::success();
    }
    
    core::Outcome configure_bounds(
        const rebuntu::observation::ObservationBounds& bounds) override {
        bounds_ = bounds;
        return core::Outcome::success();
    }
    
    core::Outcome add_observation(Observation o) override {
        if (snapshot_.observations.size() >= bounds_.collection.max_evidence_records) {
            snapshot_.truncation.was_truncated = true;
            snapshot_.truncation.reason = "Observation count exceeds maximum";
            return core::Outcome::completed();
        }
        
        FreshnessPolicy policy;
        bool is_fresh = check_fresh(o, policy);
        
        if (!policy.allow_stale && !is_fresh) {
            o.quality = ObservationQuality::kPartial;
            snapshot_.truncation.was_truncated = true;
        }
        
        snapshot_.add_observation(std::move(o));
        return core::Outcome::success();
    }
    
    core::Outcome add_fact(Fact f) override {
        if (snapshot_.facts.size() >= bounds_.collection.max_evidence_records) {
            return core::Outcome::completed();
        }
        
        snapshot_.add_fact(std::move(f));
        return core::Outcome::success();
    }
    
    core::Outcome mark_domain_complete(ObservationDomain d) override {
        if (snapshot_.state == SnapshotState::kUnknown ||
            snapshot_.state == SnapshotState::kComplete) {
            snapshot_.observed_domains.insert(d);
            snapshot_.domains_failed.erase(
                std::remove(snapshot_.domains_failed.begin(),
                           snapshot_.domains_failed.end(), to_string(d)),
                snapshot_.domains_failed.end());
        }
        return core::Outcome::success();
    }
    
    core::Outcome mark_domain_failed(ObservationDomain d, core::Error e) override {
        if (snapshot_.state == SnapshotState::kUnknown ||
            snapshot_.state == SnapshotState::kComplete) {
            snapshot_.mark_failed(d, std::move(e));
            if (snapshot_.observed_domains.empty()) {
                snapshot_.state = SnapshotState::kEmpty;
            } else {
                snapshot_.state = SnapshotState::kPartial;
            }
        }
        return core::Outcome::success();
    }
    
    core::Outcome set_snapshot_state(SnapshotState s) override {
        if (snapshot_.state == SnapshotState::kUnknown ||
            snapshot_.state == SnapshotState::kComplete) {
            snapshot_.state = s;
        }
        return core::Outcome::success();
    }
    
    std::optional<Snapshot> build() override {
        if (snapshot_.observations.empty()) {
            snapshot_.overall_quality = ObservationQuality::kUnknown;
        } else {
            size_t authoritative = 0, observed = 0, partial = 0, unknown = 0;
            for (const auto& o : snapshot_.observations) {
                switch (o.quality) {
                    case ObservationQuality::kAuthoritative: authoritative++; break;
                    case ObservationQuality::kObserved:      observed++; break;
                    case ObservationQuality::kPartial:       partial++; break;
                    default:                                 unknown++; break;
                }
            }
            
            if (authoritative > snapshot_.observations.size() / 2) {
                snapshot_.overall_quality = ObservationQuality::kAuthoritative;
            } else if (observed >= authoritative + unknown) {
                snapshot_.overall_quality = ObservationQuality::kObserved;
            } else if (partial > 0) {
                snapshot_.overall_quality = ObservationQuality::kPartial;
            } else {
                snapshot_.overall_quality = ObservationQuality::kUnknown;
            }
        }
        
        if (!snapshot_.start_time.has_value()) {
            snapshot_.start_time = snapshot_.snapshot_time;
        }
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            snapshot_.snapshot_time.time_since_epoch() - 
            snapshot_.start_time->time_since_epoch());
        snapshot_.elapsed_ms = elapsed;
        
        if (snapshot_.state == SnapshotState::kUnknown) {
            snapshot_.state = snapshot_.observations.empty() ? 
                SnapshotState::kEmpty : SnapshotState::kComplete;
        }
        
        return snapshot_;
    }

private:
    Snapshot snapshot_{};
    
    // Note: ObservationBounds comes from rebuntu::observation namespace
    // This is defined in system/observation/bounds.hpp
    rebuntu::observation::ObservationBounds bounds_{
        rebuntu::observation::PayloadSizeLimit{},
        rebuntu::observation::CollectionLimit{
            .max_processes = 1000,
            .max_services = 500,
            .max_evidence_records = 1000
        },
        rebuntu::observation::RetentionPolicy{},
        rebuntu::observation::BackpressureConfig{}
    };
    
    bool check_fresh(const Observation& o, const FreshnessPolicy& policy) {
        if (!o.acquired_at.time_since_epoch().count()) {
            return false;
        }
        
        auto now = std::chrono::system_clock::now();
        auto age = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch() - o.acquired_at.time_since_epoch());
        
        return age <= policy.max_age_ms;
    }
};

std::unique_ptr<SnapshotBuilder> make_snapshot_builder() {
    return std::make_unique<SnapshotBuilderImpl>();
}

// ============================================================================
// CurrentStateView Implementation
// ============================================================================

class CurrentStateViewImpl : public CurrentStateView {
public:
    ~CurrentStateViewImpl() override = default;
    
    std::optional<Snapshot> get_snapshot(
        const std::set<ObservationDomain>& domains,
        const rebuntu::observation::ObservationBounds& bounds) override {
        
        auto builder = make_snapshot_builder();
        
        if (!builder->start().is_success()) {
            return std::nullopt;
        }
        
        if (!builder->configure_bounds(bounds).is_success()) {
            return std::nullopt;
        }
        
        // TODO: Integrate all domain adapters
        builder->set_snapshot_state(SnapshotState::kEmpty);
        
        return builder->build();
    }
    
    std::vector<Fact> get_facts(const ObservationIdentity& subject) override {
        return {};
    }
    
    bool is_fresh(
        const ObservationIdentity& subject,
        const FreshnessPolicy& policy) override {
        return false;
    }
    
    std::optional<std::chrono::system_clock::time_point> 
    last_snapshot_time() const override {
        return std::nullopt;
    }
};

std::unique_ptr<CurrentStateView> make_current_state_view() {
    return std::make_unique<CurrentStateViewImpl>();
}

}  // namespace rebuntu::system::observation