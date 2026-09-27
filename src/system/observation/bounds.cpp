// rebuntu::observation::bounds — Observation Memory Bounds Implementation (Phase 5.52)

#include "system/observation/bounds.hpp"

namespace rebuntu::observation {

// ============================================================================
// BoundsConfiguration implementation
// ============================================================================

ObservationBounds BoundsConfiguration::make_default() {
    return ObservationBounds{
        PayloadSizeLimit{},
        CollectionLimit{},
        RetentionPolicy{},
        BackpressureConfig{},
        true  // enabled by default
    };
}

BoundsConfiguration& BoundsConfiguration::with_payload_limits(PayloadSizeLimit limits) {
    bounds_.payload = limits;
    return *this;
}

BoundsConfiguration& BoundsConfiguration::with_collection_limits(CollectionLimit limits) {
    bounds_.collection = limits;
    return *this;
}

BoundsConfiguration& BoundsConfiguration::with_retention_policy(RetentionPolicy policy) {
    bounds_.retention = policy;
    return *this;
}

BoundsConfiguration& BoundsConfiguration::with_backpressure_config(BackpressureConfig config) {
    bounds_.backpressure = config;
    return *this;
}

BoundsConfiguration& BoundsConfiguration::with_enabled(bool enabled) {
    bounds_.enabled = enabled;
    return *this;
}

}  // namespace rebuntu::observation