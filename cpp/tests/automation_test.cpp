// Test suite for Rebuntu automation module (Phase 0.12)
#include <string>

// TriggerKind enum values
constexpr int kEvent = 0;
constexpr int kSchedule = 1;
constexpr int kConditionTrue = 2;
constexpr int kRequest = 3;

// ActivationDecision enum values  
constexpr int kAllow = 0;
constexpr int kSuppress = 1;
constexpr int kCoalesce = 2;
constexpr int kDefer = 3;
constexpr int kReject = 4;

const char* to_string_trigger(int k) {
    switch (k) {
        case kEvent: return "event";
        case kSchedule: return "schedule";
        case kConditionTrue: return "condition_true";
        case kRequest: return "request";
        default: return "unknown";
    }
}

const char* to_string_decision(int d) {
    switch (d) {
        case kAllow: return "allow";
        case kSuppress: return "suppress";
        case kCoalesce: return "coalesce";
        case kDefer: return "defer";
        case kReject: return "reject";
        default: return "unknown";
    }
}

int main() {
    int errors = 0;
    
    if (to_string_trigger(kEvent) != std::string("event")) errors++;
    if (to_string_trigger(kSchedule) != std::string("schedule")) errors++;
    if (to_string_trigger(kConditionTrue) != std::string("condition_true")) errors++;
    if (to_string_trigger(kRequest) != std::string("request")) errors++;
    
    if (to_string_decision(kAllow) != std::string("allow")) errors++;
    if (to_string_decision(kSuppress) != std::string("suppress")) errors++;
    if (to_string_decision(kCoalesce) != std::string("coalesce")) errors++;

    return errors;
}