// rebuntu::runtime::controller — Runtime Control Operations Implementation (Phase 4.6)
//
// This implements the Controller interface for runtime control operations.

#include <runtime/controller.hpp>
#include <runtime/cancellation/error.hpp>
#include <string>

namespace rebuntu::runtime::controller {

// ============================================================================
// ControllerBuilder
// ============================================================================

ControllerBuilder::ControllerBuilder() {
    default_timeout_ = std::chrono::milliseconds(30000);  // Default 30 seconds
}

ControllerBuilder& ControllerBuilder::set_default_timeout(std::chrono::milliseconds ms) {
    default_timeout_ = ms;
    return *this;
}

ControllerBuilder& ControllerBuilder::add_observer(std::shared_ptr<ControlObserver> observer) {
    if (observer) {
        observers_.push_back(observer);
    }
    return *this;
}

ControllerBuilder& ControllerBuilder::set_cancellation_token(CancellationToken token) {
    cancellation_token_ = std::move(token);
    return *this;
}

std::unique_ptr<Controller> ControllerBuilder::build() {
    // For now, this is a placeholder for future implementation
    // The actual controller implementation would integrate with:
    // - Runner: for execution control (cancel)
    // - Systemd/D-Bus: for service control
    // - Process management: for process control
    
    return nullptr;  // Placeholder until full implementation
}

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<Controller> make_controller() {
    return ControllerBuilder{}.build();
}

std::unique_ptr<Controller> make_controller_with_timeout(std::chrono::milliseconds timeout) {
    return ControllerBuilder{}
        .set_default_timeout(timeout)
        .build();
}

}  // namespace rebuntu::runtime::controller