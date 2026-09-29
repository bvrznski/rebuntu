// rebuntu::system::observation::SnapshotBuilderImpl — Snapshot Builder Implementation (Phase 7.2)

#include "system/observation/snapshot_builder.hpp"
#include <optional>

namespace rebuntu::system::observation {

// ============================================================================
// SnapshotBuilderImpl Implementation
// ============================================================================

SnapshotBuilderImpl::SnapshotBuilderImpl(const rebuntu::observation::ObservationBounds& bounds)
    : bounds_(bounds), started_(false) {
}

SnapshotBuilderImpl::~SnapshotBuilderImpl() = default;

core::Outcome SnapshotBuilderImpl::start(const std::string& id) {
    if (started_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "SnapshotBuilderImpl: start() called twice without build()");
    }
    
    snapshot_ = Snapshot{};
    started_ = true;
    return core::Outcome::success();
}

core::Outcome SnapshotBuilderImpl::configure_bounds(const rebuntu::observation::ObservationBounds& bounds) {
    if (started_) {
        return core::Outcome::failure("E_CANNOT_CHANGE_BOUNDS", "SnapshotBuilderImpl: cannot configure bounds after start()");
    }
    
    bounds_ = bounds;
    return core::Outcome::success();
}

core::Outcome SnapshotBuilderImpl::add_observation(Observation o) {
    if (!started_) {
        return core::Outcome::failure("E_NOT_STARTED", "SnapshotBuilderImpl: add_observation() called before start()");
    }
    
    // Check bounds - max observations per request
    const auto& collection_limit = bounds_.collection;
    if (snapshot_.observations.size() >= collection_limit.max_evidence_records) {
        snapshot_.truncation = Truncation::with_reason("Maximum observations per request exceeded");
        return core::Outcome::failure("E_BOUNDS_TRUNCATED", "SnapshotBuilderImpl: observation truncated by bounds");
    }
    
    // Note: timeout enforcement is handled at caller level via state_acquisition_service
    snapshot_.add_observation(std::move(o));
    return core::Outcome::success();
}

core::Outcome SnapshotBuilderImpl::add_fact(Fact f) {
    if (!started_) {
        return core::Outcome::failure("E_NOT_STARTED", "SnapshotBuilderImpl: add_fact() called before start()");
    }
    
    snapshot_.add_fact(std::move(f));
    return core::Outcome::success();
}

core::Outcome SnapshotBuilderImpl::mark_domain_complete(ObservationDomain d) {
    (void)d;  // unused
    if (!started_) {
        return core::Outcome::failure("E_NOT_STARTED", "SnapshotBuilderImpl: mark_domain_complete() called before start()");
    }
    return core::Outcome::success();
}

core::Outcome SnapshotBuilderImpl::mark_domain_failed(ObservationDomain d, core::Error e) {
    (void)d;  // unused
    if (!started_) {
        return core::Outcome::failure("E_NOT_STARTED", "SnapshotBuilderImpl: mark_domain_failed() called before start()");
    }
    
    snapshot_.mark_failed(d, std::move(e));
    return core::Outcome::success();
}

core::Outcome SnapshotBuilderImpl::set_snapshot_state(SnapshotState s) {
    (void)s;  // unused
    if (!started_) {
        return core::Outcome::failure("E_NOT_STARTED", "SnapshotBuilderImpl: set_snapshot_state() called before start()");
    }
    
    snapshot_.state = s;
    return core::Outcome::success();
}

std::optional<Snapshot> SnapshotBuilderImpl::build() {
    if (!started_) {
        started_ = true;
        // Return a fresh snapshot when build called without start
        return std::make_optional(Snapshot{});
    }
    
    auto result = std::make_optional(snapshot_);
    started_ = false;
    return result;
}

SnapshotBuilderImpl::Progress SnapshotBuilderImpl::progress() const {
    Progress p;
    p.observations_added = snapshot_.observations.size();
    p.facts_added = snapshot_.facts.size();
    
    for (const auto& obs : snapshot_.observations) {
        p.domains_complete.insert(obs.subject.domain);
    }
    
    return p;
}

// ============================================================================
// CurrentStateViewImpl Implementation
// ============================================================================

CurrentStateViewImpl::CurrentStateViewImpl() {
    domain_ttls_[ObservationDomain::kProcess] = std::chrono::seconds(10);
    domain_ttls_[ObservationDomain::kService] = std::chrono::seconds(30);
}

CurrentStateViewImpl::~CurrentStateViewImpl() = default;

std::optional<Snapshot> CurrentStateViewImpl::get_snapshot(
        const std::set<ObservationDomain>& domains,
        const rebuntu::observation::ObservationBounds& bounds) {
    
    (void)bounds;  // unused - use configured bounds
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto snapshot = Snapshot::make();
    auto now = std::chrono::system_clock::now();
    
    for (const auto& adapter : adapters_) {
        auto domain = adapter->domain();
        
        // Skip domains not in the requested set
        if (!domains.empty() && domains.count(domain) == 0) {
            continue;
        }
        
        std::vector<Observation> observations;
        auto outcome = adapter->observe(std::nullopt, observations);
        
        if (outcome.status == core::SemanticStatus::kSuccess || 
            outcome.status == core::SemanticStatus::kPartial) {
            
            for (auto& obs : observations) {
                obs.acquired_at = now;
                snapshot.add_observation(std::move(obs));
            }
        } else if (outcome.error.has_value()) {
            // Record failed domain with error
            snapshot.mark_failed(domain, std::move(outcome.error.value()));
        }
    }
    
    return std::make_optional(snapshot);
}

std::vector<Fact> CurrentStateViewImpl::get_facts(const ObservationIdentity& subject) {
    (void)subject;
    return {};
}

bool CurrentStateViewImpl::is_fresh(
        const ObservationIdentity& subject,
        const FreshnessPolicy& policy) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (last_snapshot_time_.time_since_epoch().count() == 0) {
        return false;
    }
    
    auto now = std::chrono::system_clock::now();
    auto age_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_snapshot_time_);
    
    auto ttl_it = domain_ttls_.find(subject.domain);
    auto ttl = (ttl_it != domain_ttls_.end()) ? 
        ttl_it->second : policy.max_age_ms;
    
    return age_ms <= ttl;
}

std::optional<std::chrono::system_clock::time_point> 
CurrentStateViewImpl::last_snapshot_time() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return last_snapshot_time_;
}

void CurrentStateViewImpl::register_adapter(std::unique_ptr<ObservationAdapter> adapter) {
    std::lock_guard<std::mutex> lock(mutex_);
    adapters_.push_back(std::move(adapter));
}

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<SnapshotBuilderImpl> make_snapshot_builder_impl(
        const rebuntu::observation::ObservationBounds& bounds) {
    return std::make_unique<SnapshotBuilderImpl>(bounds);
}

std::unique_ptr<CurrentStateViewImpl> make_current_state_view_impl() {
    return std::make_unique<CurrentStateViewImpl>();
}

}  // namespace rebuntu::system::observation