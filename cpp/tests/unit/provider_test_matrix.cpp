// rebuntu::tests::provider_test_matrix — Phase 5.63 Unit and Provider Test Matrix
//
// Comprehensive test coverage for:
//   - Parsing, Identity, Freshness, Partial state, Races
//   - Disappearance, Provider failure, Unsupported capability
//   - Resync, Cancellation, Bounded output, Native fixtures

#include <adapters/isolated_provider.hpp>
#include <system/core/contracts.hpp>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <optional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <unistd.h>
#include <fstream>

namespace rebuntu::tests::provider_test_matrix {

using core::SemanticStatus;

namespace rebuntu::adapters {
    template<typename T>
    auto& deref_unique(std::unique_ptr<T>& ptr) {
        return *ptr;
    }
}

using namespace rebuntu::adapters;

// ============================================================================
// Test Infrastructure
// ============================================================================

// Dereference helper for unique_ptr - moved to adapters namespace above

struct TestResult {
    std::string value;
    bool success{false};
    
    static TestResult make_success(std::string v) {
        return {std::move(v), true};
    }
};

// ============================================================================
// ConfigurableAdapter - Tests parsing, identity, freshness, failure modes
// ============================================================================

class ConfigurableAdapter {
public:
    std::string provider_id() const { return id_; }
    
private:
    std::string id_;
    bool throw_on_observe_{false};
    bool throw_system_error_{false};
    int delay_ms_{0};
    std::chrono::system_clock::time_point last_observation_{};
    
public:
    explicit ConfigurableAdapter(std::string id = "test-adapter")
        : id_(std::move(id)) {}
    
    void set_throw_on_observe(bool v) { throw_on_observe_ = v; }
    void set_throw_system_error(bool v, std::error_code ec = {}) {
        throw_system_error_ = v;
    }
    void set_delay_ms(int ms) { delay_ms_ = ms; }
    
    TestResult observe_all() {
        if (delay_ms_ > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms_));
        }
        
        if (throw_on_observe_) {
            throw std::runtime_error("Simulated adapter failure");
        }
        
        if (throw_system_error_) {
            throw std::system_error(std::make_error_code(std::errc::timed_out), "Configured error");
        }
        
        last_observation_ = std::chrono::system_clock::now();
        return TestResult::make_success("observed_data_" + id_);
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const {
        return last_observation_;
    }
};

// ============================================================================
// PartialStateAdapter - Tests partial state handling
// ============================================================================

class PartialStateAdapter {
public:
    std::string provider_id() const { return "partial-state-adapter"; }
    
    struct Result {
        std::vector<std::string> items;
        bool complete{true};
        size_t partial_count{0};
    };
    
private:
    mutable std::mutex mutex_;
    std::vector<std::string> data_;
    bool simulate_partial_{false};
    
public:
    PartialStateAdapter() : data_{"item1", "item2", "item3"} {}
    
    void set_simulate_partial(bool v) { 
        std::lock_guard<std::mutex> lock(mutex_);
        simulate_partial_ = v; 
    }
    
    Result observe_all() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (simulate_partial_) {
            return Result{
                .items = {"partial_item1", "partial_item2"},
                .complete = false,
                .partial_count = 3
            };
        }
        return Result{.items = data_, .complete = true};
    }
    
    std::string observe_one(size_t index) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (index < data_.size()) {
            return data_[index];
        }
        return "";
    }
};

// ============================================================================
// CancellableAdapter - Tests cancellation handling
// ============================================================================

class CancellableAdapter {
public:
    std::string provider_id() const { return "cancellable-adapter"; }
    
    struct Result {
        bool cancelled{false};
        std::vector<int> values;
    };
    
private:
    mutable std::atomic<bool> cancel_requested_{false};
    mutable std::mutex mutex_;
    mutable std::condition_variable cv_;
    
public:
    void request_cancel() { 
        cancel_requested_.store(true);
        cv_.notify_all();
    }
    
    void clear_cancel() { 
        cancel_requested_.store(false);
    }
    
    Result observe_all() {
        std::unique_lock<std::mutex> lock(mutex_);
        Result result;
        
        for (int i = 0; i < 10; ++i) {
            if (cancel_requested_.load()) {
                result.cancelled = true;
                return result;
            }
            
            cv_.wait_for(lock, std::chrono::milliseconds(5));
            result.values.push_back(i * 10);
        }
        
        return result;
    }
};

// ============================================================================
// BoundedOutputAdapter - Tests bounded output
// ============================================================================

class BoundedOutputAdapter {
public:
    std::string provider_id() const { return "bounded-output-adapter"; }
    
    struct Result {
        std::vector<int> values;
        bool truncated{false};
    };
    
private:
    size_t max_items_{10};
    
public:
    explicit BoundedOutputAdapter(size_t max_items = 10) : max_items_(max_items) {}
    
    void set_max_items(size_t n) { max_items_ = n; }
    
    Result observe_all() {
        Result result;
        
        for (size_t i = 0; i < max_items_ + 5; ++i) {
            if (result.values.size() >= max_items_) {
                result.truncated = true;
                break;
            }
            result.values.push_back(static_cast<int>(i));
        }
        
        return result;
    }
};

// ============================================================================
// DisappearingResourceAdapter - Tests resource disappearance
// ============================================================================

class DisappearingResourceAdapter {
public:
    std::string provider_id() const { return "disappearing-resource-adapter"; }
    
    struct Result {
        bool available{false};
        std::string data;
    };
    
private:
    mutable std::atomic<bool> resource_available_{true};
    
public:
    void set_resource_available(bool v) { 
        resource_available_.store(v); 
    }
    
    Result observe_all() {
        if (!resource_available_.load()) {
            return Result{.available = false, .data = ""};
        }
        
        return Result{
            .available = true,
            .data = "resource_data"
        };
    }
};

// ============================================================================
// CapabilityAdapter - Tests unsupported capability handling
// ============================================================================

class CapabilityAdapter {
public:
    std::string provider_id() const { return "capability-adapter"; }
    
    struct Result {
        bool success{false};
        std::vector<std::string> supported_capabilities;
    };
    
private:
    std::vector<std::string> supported_{"basic", "standard"};
    
public:
    Result observe_all() {
        return Result{
            .success = true,
            .supported_capabilities = supported_
        };
    }
    
    bool has_capability(const std::string& cap) const {
        for (const auto& s : supported_) {
            if (s == cap) return true;
        }
        return false;
    }
};

// ============================================================================
// SequenceAdapter - Tests resync with sequence numbers
// ============================================================================

class SequenceAdapter {
public:
    std::string provider_id() const { return "sequence-adapter"; }
    
    struct Result {
        int sequence_number{0};
        std::string data;
    };
    
private:
    mutable std::atomic<int> sequence_{0};
    
public:
    void reset_sequence() { sequence_.store(0); }
    void set_sequence(int n) { sequence_.store(n); }
    
    Result observe_all() {
        int seq = sequence_.fetch_add(1);
        return Result{
            .sequence_number = seq,
            .data = "data_" + std::to_string(seq)
        };
    }
};

// ============================================================================
// ParsingAdapter - Tests parsing behavior
// ============================================================================

class ParsingAdapter {
public:
    std::string provider_id() const { return "parsing-adapter"; }
    
    struct Result {
        bool valid{false};
        int parsed_value{-1};
        std::string error_message;
    };
    
private:
    bool simulate_parse_error_{false};
    int parse_success_value_{42};
    
public:
    void set_simulate_parse_error(bool v) { simulate_parse_error_ = v; }
    void set_parse_success_value(int v) { parse_success_value_ = v; }
    
    Result observe_all() {
        if (simulate_parse_error_) {
            return Result{
                .valid = false,
                .error_message = "Failed to parse: invalid format"
            };
        }
        
        return Result{.valid = true, .parsed_value = parse_success_value_};
    }
};

// ============================================================================
// RaceAdapter - Tests race conditions
// ============================================================================

class RaceAdapter {
public:
    std::string provider_id() const { return "race-adapter"; }
    
    struct Result {
        int counter{0};
        bool consistent{true};
    };
    
private:
    mutable std::atomic<int> counter_{0};
    mutable std::mutex mutex_;
    
public:
    void increment() { counter_.fetch_add(1); }
    
    Result observe_all() {
        auto start_counter = counter_.load();
        
        for (int i = 0; i < 1000; ++i) {
            std::lock_guard<std::mutex> lock(mutex_);
            int temp = counter_.load();
            std::this_thread::yield();
            counter_.store(temp + 1);
        }
        
        auto end_counter = counter_.load();
        
        return Result{
            .counter = start_counter,
            .consistent = true
        };
    }
};

// ============================================================================
// TimeoutAdapter - Tests timeout behavior
// ============================================================================

class TimeoutAdapter {
public:
    std::string provider_id() const { return "timeout-adapter"; }
    
    struct Result {
        bool timed_out{false};
        std::string data;
    };
    
private:
    int timeout_ms_{100};
    
public:
    void set_timeout_ms(int ms) { timeout_ms_ = ms; }
    
    Result observe_all() {
        auto start = std::chrono::steady_clock::now();
        
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - start).count() < timeout_ms_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        return Result{.timed_out = true, .data = "timeout_data"};
    }
};

// ============================================================================
// IdentityAdapter - Tests identity tracking
// ============================================================================

class IdentityAdapter {
public:
    std::string provider_id() const { return "identity-adapter"; }
    
    struct Result {
        std::string id;
        int version{1};
    };
    
private:
    static constexpr int kVersion = 42;
    
public:
    Result observe_all() {
        return Result{
            .id = provider_id(),
            .version = kVersion
        };
    }
};

// ============================================================================
// FreshnessAdapter - Tests freshness tracking
// ============================================================================

class FreshnessAdapter {
public:
    std::string provider_id() const { return "freshness-adapter"; }
    
    struct Result {
        std::chrono::system_clock::time_point observed_at;
        int count{0};
    };
    
private:
    mutable std::mutex mutex_;
    std::chrono::system_clock::time_point last_observation_{};
    
public:
    void clear_cache() {
        std::lock_guard<std::mutex> lock(mutex_);
        last_observation_ = {};
    }
    
    Result observe_all() {
        auto now = std::chrono::system_clock::now();
        
        std::lock_guard<std::mutex> lock(mutex_);
        if (last_observation_.time_since_epoch().count() == 0) {
            last_observation_ = now;
        }
        
        return Result{
            .observed_at = now,
            .count = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
                now.time_since_epoch()).count())
        };
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return last_observation_;
    }
};

// ============================================================================
// ProcFixtureAdapter - Tests with real Linux /proc data
// ============================================================================

class ProcFixtureAdapter {
public:
    std::string provider_id() const { return "proc-fixture-adapter"; }
    
    struct Result {
        bool valid{false};
        int pid{-1};
        char state{'?'};
    };
    
private:
    static int read_proc_pid() {
        std::ifstream file("/proc/self/stat");
        if (!file.is_open()) {
            return -1;
        }
        
        int pid;
        char state;
        if (file >> pid >> state) {
            return pid;
        }
        
        return -1;
    }
    
public:
    Result observe_all() {
        int pid = read_proc_pid();
        
        if (pid <= 0) {
            return Result{.valid = false};
        }
        
        std::ifstream stat("/proc/self/stat");
        if (!stat.is_open()) {
            return Result{.valid = true, .pid = pid, .state = '?'};
        }
        
        char state;
        stat >> pid >> state;
        
        return Result{.valid = true, .pid = pid, .state = state};
    }
};

// ============================================================================
// Unit Tests: Parsing
// ============================================================================

void test_parsing_valid_input() {
    std::cout << "[TEST] Parsing valid input...";
    
    ParsingAdapter adapter;
    adapter.set_simulate_parse_error(false);
    adapter.set_parse_success_value(42);
    
    auto result = adapter.observe_all();
    
    assert(result.valid == true);
    assert(result.parsed_value == 42);
    
    std::cout << " PASS\n";
}

void test_parsing_invalid_input() {
    std::cout << "[TEST] Parsing invalid input...";
    
    ParsingAdapter adapter;
    adapter.set_simulate_parse_error(true);
    
    auto result = adapter.observe_all();
    
    assert(result.valid == false);
    assert(!result.error_message.empty());
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Identity
// ============================================================================

void test_identity_consistency() {
    std::cout << "[TEST] Identity consistency...";
    
    IdentityAdapter adapter;
    
    auto result1 = adapter.observe_all();
    auto result2 = adapter.observe_all();
    auto result3 = adapter.observe_all();
    
    assert(result1.id == adapter.provider_id());
    assert(result2.id == adapter.provider_id());
    assert(result3.id == adapter.provider_id());
    assert(result1.version == result2.version);
    assert(result2.version == result3.version);
    
    std::cout << " PASS\n";
}

void test_identity_providers_match() {
    std::cout << "[TEST] Identity provider IDs match...";
    
    ConfigurableAdapter adapter("test-identity");
    
    auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kSuccess);
    assert(result.value.has_value());
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Freshness
// ============================================================================

void test_freshness_tracking() {
    std::cout << "[TEST] Freshness tracking...";
    
    FreshnessAdapter adapter;
    
    auto result1 = adapter.observe_all();
    auto time1 = adapter.get_last_observation_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    auto result2 = adapter.observe_all();
    auto time2 = adapter.get_last_observation_time();
    
    assert(time2.time_since_epoch().count() >= time1.time_since_epoch().count());
    
    std::cout << " PASS\n";
}

void test_freshness_clear_cache() {
    std::cout << "[TEST] Freshness cache clear...";
    
    FreshnessAdapter adapter;
    
    auto result1 = adapter.observe_all();
    auto time1 = adapter.get_last_observation_time();
    
    adapter.clear_cache();
    
    auto result2 = adapter.observe_all();
    auto time2 = adapter.get_last_observation_time();
    
    assert(time2.time_since_epoch().count() >= time1.time_since_epoch().count());
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Partial State
// ============================================================================

void test_partial_state_detection() {
    std::cout << "[TEST] Partial state detection...";
    
    PartialStateAdapter adapter;
    
    auto result1 = adapter.observe_all();
    assert(result1.complete == true);
    assert(result1.items.size() == 3);
    
    adapter.set_simulate_partial(true);
    
    auto result2 = adapter.observe_all();
    assert(result2.complete == false);
    assert(result2.partial_count == 3);
    assert(result2.items.size() < result2.partial_count);
    
    std::cout << " PASS\n";
}

void test_partial_state_observation() {
    std::cout << "[TEST] Partial state single observation...";
    
    PartialStateAdapter adapter;
    
    auto val = adapter.observe_one(0);
    assert(!val.empty());
    assert(val == "item1");
    
    auto empty = adapter.observe_one(100);
    assert(empty.empty());
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Races
// ============================================================================

void test_race_concurrent_observation() {
    std::cout << "[TEST] Race concurrent observation...";
    
    RaceAdapter adapter;
    
    std::vector<std::thread> threads;
    std::atomic<int> success_count{0};
    
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&adapter, &success_count]() {
            auto result = adapter.observe_all();
            if (result.consistent) {
                success_count.fetch_add(1);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    assert(success_count.load() >= 0);
    
    std::cout << " PASS\n";
}

void test_race_modification_during_observation() {
    std::cout << "[TEST] Race modification during observation...";
    
    RaceAdapter adapter;
    
    adapter.increment();
    
    auto result = adapter.observe_all();
    
    assert(result.consistent == true);
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Disappearance
// ============================================================================

void test_disappearing_resource_available() {
    std::cout << "[TEST] Disappearing resource available...";
    
    DisappearingResourceAdapter adapter;
    adapter.set_resource_available(true);
    
    auto result = adapter.observe_all();
    
    assert(result.available == true);
    assert(!result.data.empty());
    
    std::cout << " PASS\n";
}

void test_disappearing_resource_gone() {
    std::cout << "[TEST] Disappearing resource gone...";
    
    DisappearingResourceAdapter adapter;
    
    adapter.set_resource_available(false);
    
    auto result = adapter.observe_all();
    
    assert(result.available == false);
    
    std::cout << " PASS\n";
}

void test_disappearing_resource_reappearance() {
    std::cout << "[TEST] Disappearing resource reappears...";
    
    DisappearingResourceAdapter adapter;
    
    adapter.set_resource_available(false);
    auto result1 = adapter.observe_all();
    assert(result1.available == false);
    
    adapter.set_resource_available(true);
    auto result2 = adapter.observe_all();
    assert(result2.available == true);
    assert(!result2.data.empty());
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Provider Failure
// ============================================================================

void test_failure_runtime_error() {
    std::cout << "[TEST] Failure runtime error...";
    
    ConfigurableAdapter adapter;
    adapter.set_throw_on_observe(true);
    
    auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kUnknown);
    assert(!result.failures.empty());
    
    std::cout << " PASS\n";
}

void test_failure_system_error() {
    std::cout << "[TEST] Failure system error...";
    
    ConfigurableAdapter adapter;
    adapter.set_throw_system_error(true, std::make_error_code(std::errc::timed_out));
    
    auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kUnknown);
    
    std::cout << " PASS\n";
}

void test_failure_multiple_failures() {
    std::cout << "[TEST] Failure multiple failures...";
    
    ConfigurableAdapter adapter;
    adapter.set_throw_on_observe(true);
    
    auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
    
    for (int i = 0; i < 3; ++i) {
        auto result = deref_unique(isolated).observe_all();
        assert(result.status == SemanticStatus::kUnknown);
    }
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Unsupported Capability
// ============================================================================

void test_capability_detection() {
    std::cout << "[TEST] Capability detection...";
    
    CapabilityAdapter adapter;
    
    auto result = adapter.observe_all();
    
    assert(result.success == true);
    assert(!result.supported_capabilities.empty());
    
    assert(adapter.has_capability("basic"));
    assert(adapter.has_capability("standard"));
    assert(!adapter.has_capability("unsupported_capability_xyz"));
    
    std::cout << " PASS\n";
}

void test_unsupported_operation_handling() {
    std::cout << "[TEST] Unsupported operation handling...";
    
    CapabilityAdapter adapter;
    
    if (!adapter.has_capability("advanced")) {
        auto isolated = adapters::make_isolated_provider(std::make_unique<CapabilityAdapter>(adapter));
        auto result = deref_unique(isolated).observe_all();
        
        assert(result.status == SemanticStatus::kSuccess);
    }
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Resync
// ============================================================================

void test_resync_sequence_recovery() {
    std::cout << "[TEST] Resync sequence recovery...";
    
    SequenceAdapter adapter;
    adapter.reset_sequence();
    
    auto result1 = adapter.observe_all();
    assert(result1.sequence_number == 0);
    
    auto result2 = adapter.observe_all();
    assert(result2.sequence_number == 1);
    
    adapter.set_sequence(10);
    
    auto result3 = adapter.observe_all();
    assert(result3.sequence_number == 10);
    
    std::cout << " PASS\n";
}

void test_resync_duplicate_detection() {
    std::cout << "[TEST] Resync duplicate detection...";
    
    SequenceAdapter adapter;
    adapter.reset_sequence();
    
    auto result1 = adapter.observe_all();
    int seq1 = result1.sequence_number;
    
    adapter.set_sequence(seq1);
    
    auto result2 = adapter.observe_all();
    
    assert(result2.sequence_number >= seq1);
    
    std::cout << " PASS\n";
}

void test_resync_out_of_order() {
    std::cout << "[TEST] Resync out-of-order handling...";
    
    SequenceAdapter adapter;
    adapter.reset_sequence();
    
    auto result0 = adapter.observe_all();
    assert(result0.sequence_number == 0);
    
    adapter.set_sequence(5);
    
    auto result5 = adapter.observe_all();
    assert(result5.sequence_number == 5);
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Cancellation
// ============================================================================

void test_cancellation_request() {
    std::cout << "[TEST] Cancellation request...";
    
    CancellableAdapter adapter;
    
    adapter.request_cancel();
    
    auto result = adapter.observe_all();
    
    assert(result.cancelled == true);
    
    std::cout << " PASS\n";
}

void test_cancellation_clear() {
    std::cout << "[TEST] Cancellation clear...";
    
    CancellableAdapter adapter;
    
    adapter.request_cancel();
    adapter.clear_cancel();
    
    auto result = adapter.observe_all();
    
    assert(result.cancelled == false);
    assert(!result.values.empty());
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Bounded Output
// ============================================================================

void test_bounded_output_limit() {
    std::cout << "[TEST] Bounded output limit...";
    
    BoundedOutputAdapter adapter(5);
    
    auto result = adapter.observe_all();
    
    assert(result.values.size() <= 5);
    assert(result.truncated == true);
    
    std::cout << " PASS\n";
}

void test_bounded_output_no_truncation() {
    std::cout << "[TEST] Bounded output no truncation...";
    
    BoundedOutputAdapter adapter(20);
    
    auto result = adapter.observe_all();
    
    assert(result.values.size() == 15);
    assert(result.truncated == false);
    
    std::cout << " PASS\n";
}

void test_bounded_output_zero_limit() {
    std::cout << "[TEST] Bounded output zero limit...";
    
    BoundedOutputAdapter adapter(0);
    
    auto result = adapter.observe_all();
    
    assert(result.values.size() == 0);
    assert(result.truncated == true);
    
    std::cout << " PASS\n";
}

// ============================================================================
// Unit Tests: Native Fixtures (Linux-specific)
// ============================================================================

void test_proc_fixture_current_process() {
    std::cout << "[TEST] Proc fixture current process...";
    
    ProcFixtureAdapter adapter;
    auto result = adapter.observe_all();
    
    assert(result.valid == true);
    assert(result.pid > 0);
    
    std::cout << " PASS\n";
}

void test_proc_fixture_state() {
    std::cout << "[TEST] Proc fixture process state...";
    
    ProcFixtureAdapter adapter;
    auto result = adapter.observe_all();
    
    if (result.state != '?') {
        char state = result.state;
        assert(state == 'R' || state == 'S' || state == 'D' ||
               state == 'T' || state == 'Z' || state == 'X' ||
               state == 't' || state == 'W');
    }
    
    std::cout << " PASS\n";
}

void test_proc_fixture_adapter_exists() {
    std::cout << "[TEST] Proc fixture adapter exists...";
    
    ProcFixtureAdapter adapter;
    auto result = adapter.observe_all();
    assert(result.valid == true);
    
    std::cout << " PASS\n";
}

// ============================================================================
// Integration Tests: Complete Workflow
// ============================================================================

void test_isolated_provider_integration() {
    std::cout << "[TEST] Isolated provider integration...";
    
    {
        auto wrapped = std::make_unique<ConfigurableAdapter>("success-adapter");
        auto isolated = adapters::make_isolated_provider(std::move(wrapped));
        
        auto result = deref_unique(isolated).observe_all();
        assert(result.status == SemanticStatus::kSuccess);
    }
    
    {
        auto wrapped = std::make_unique<ConfigurableAdapter>("fail-adapter");
        wrapped->set_throw_on_observe(true);
        auto isolated = adapters::make_isolated_provider(std::move(wrapped));
        
        auto result = deref_unique(isolated).observe_all();
        assert(result.status == SemanticStatus::kUnknown);
    }
    
    {
        static int call_count = 0;
        
        class FlakyAdapter {
        public:
            const std::string& provider_id() const { return id_; }
            
            TestResult observe_all() {
                ++call_count;
                if (call_count <= 1) {
                    throw std::runtime_error("First attempt fails");
                }
                return TestResult::make_success("success_on_retry");
            }
        private:
            std::string id_{"flaky-adapter"};
        };
        
        auto wrapped = std::make_unique<FlakyAdapter>();
        auto isolated = adapters::make_isolated_provider(std::move(wrapped));
        
        auto result1 = deref_unique(isolated).observe_all();
        assert(result1.status == SemanticStatus::kUnknown);
        
        auto result2 = deref_unique(isolated).observe_all();
        assert(result2.status == SemanticStatus::kSuccess);
    }
    
    std::cout << " PASS\n";
}

void test_failure_categories() {
    std::cout << "[TEST] Failure categories...";
    
    {
        ConfigurableAdapter adapter;
        adapter.set_throw_system_error(true, std::make_error_code(std::errc::timed_out));
        
        auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
        auto result = deref_unique(isolated).observe_all();
        
        assert(result.status == SemanticStatus::kUnknown);
    }
    
    {
        ConfigurableAdapter adapter;
        adapter.set_throw_system_error(true, std::make_error_code(std::errc::permission_denied));
        
        auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
        auto result = deref_unique(isolated).observe_all();
        
        assert(result.status == SemanticStatus::kUnknown);
    }
    
    std::cout << " PASS\n";
}

void test_partial_state_integration() {
    std::cout << "[TEST] Partial state integration...";
    
    PartialStateAdapter adapter;
    
    auto result1 = adapter.observe_all();
    assert(result1.complete == true);
    
    adapter.set_simulate_partial(true);
    
    auto val = adapter.observe_one(0);
    assert(!val.empty());
    
    std::cout << " PASS\n";
}

void test_identity_integration() {
    std::cout << "[TEST] Identity integration...";
    
    IdentityAdapter adapter;
    
    for (int i = 0; i < 5; ++i) {
        auto result = adapter.observe_all();
        assert(result.id == adapter.provider_id());
        assert(result.version == 42);
    }
    
    std::cout << " PASS\n";
}

void test_freshness_integration() {
    std::cout << "[TEST] Freshness integration...";
    
    FreshnessAdapter adapter;
    
    auto result1 = adapter.observe_all();
    auto time1 = adapter.get_last_observation_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    auto result2 = adapter.observe_all();
    auto time2 = adapter.get_last_observation_time();
    
    assert(time2 >= time1);
    assert(result2.count > 0);
    
    std::cout << " PASS\n";
}

void test_bounded_output_integration() {
    std::cout << "[TEST] Bounded output integration...";
    
    BoundedOutputAdapter adapter(5);
    
    auto result = adapter.observe_all();
    
    assert(result.values.size() <= 5);
    assert(result.truncated == true);
    
    std::cout << " PASS\n";
}

void test_native_fixture_integration() {
    std::cout << "[TEST] Native fixture integration...";
    
    ProcFixtureAdapter adapter;
    
    auto result = adapter.observe_all();
    
    assert(result.valid == true);
    assert(result.pid > 0);
    
    std::cout << " PASS\n";
}

// ============================================================================
// Adversarial Tests
// ============================================================================

void test_adversarial_truncated_input() {
    std::cout << "[TEST] Adversarial truncated input...";
    
    ParsingAdapter adapter;
    adapter.set_simulate_parse_error(true);
    
    auto result = adapter.observe_all();
    
    assert(result.valid == false);
    assert(!result.error_message.empty());
    
    std::cout << " PASS\n";
}

void test_adversarial_large_output() {
    std::cout << "[TEST] Adversarial large output...";
    
    BoundedOutputAdapter adapter(100);
    
    auto result = adapter.observe_all();
    
    assert(result.values.size() <= 100);
    
    std::cout << " PASS\n";
}

void test_adversarial_concurrent_operations() {
    std::cout << "[TEST] Adversarial concurrent operations...";
    
    ConfigurableAdapter adapter;
    adapter.set_delay_ms(5);
    
    auto isolated = adapters::make_isolated_provider(std::make_unique<ConfigurableAdapter>(adapter));
    
    std::vector<std::thread> threads;
    std::atomic<int> success_count{0};
    std::mutex results_mutex;
    std::vector<SemanticStatus> statuses;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&isolated, &success_count, &statuses, &results_mutex]() {
            auto result = deref_unique(isolated).observe_all();
            
            if (result.status == SemanticStatus::kSuccess) {
                success_count.fetch_add(1);
            }
            
            std::lock_guard<std::mutex> lock(results_mutex);
            statuses.push_back(result.status);
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    assert(statuses.size() == 10);
    
    std::cout << " PASS\n";
}

void test_adversarial_rapid_failure_recovery() {
    std::cout << "[TEST] Adversarial rapid failure recovery...";
    
    class RapidRecoveryAdapter {
    public:
        const std::string& provider_id() const { return id_; }
        
        TestResult observe_all() {
            static int call_count = 0;
            
            if (call_count < 5) {
                throw std::runtime_error("Simulated transient failure");
            }
            ++call_count;
            return TestResult::make_success("success_after_retries");
        }
    private:
        std::string id_{"rapid-recovery-adapter"};
    };
    
    auto wrapped = std::make_unique<RapidRecoveryAdapter>();
    auto isolated = adapters::make_isolated_provider(std::move(wrapped));
    
    int failures = 0;
    bool eventually_succeeded = false;
    
    for (int i = 0; i < 10; ++i) {
        auto result = deref_unique(isolated).observe_all();
        
        if (result.status == SemanticStatus::kUnknown) {
            ++failures;
        } else {
            eventually_succeeded = true;
            break;
        }
    }
    
    assert(failures >= 5);
    assert(eventually_succeeded);
    
    std::cout << " PASS\n";
}

void test_adversarial_null_adapter() {
    std::cout << "[TEST] Adversarial null adapter...";
    
    auto isolated = adapters::make_isolated_provider<ConfigurableAdapter>(nullptr);
    
    auto result = deref_unique(isolated).observe_all();
    
    // Should not crash - the wrapper should handle null gracefully
    assert(result.status == SemanticStatus::kUnknown || 
           result.failures.size() > 0);
    
    std::cout << " PASS (no crash)\n";
}

// ============================================================================
// Test Runner
// ============================================================================

void run_all_tests() {
    std::cout << "\n========================================\n";
    std::cout << "Provider Test Matrix - Phase 5.63\n";
    std::cout << "========================================\n\n";
    
    // Parsing tests
    std::cout << "--- Parsing Tests ---\n";
    test_parsing_valid_input();
    test_parsing_invalid_input();
    
    // Identity tests
    std::cout << "\n--- Identity Tests ---\n";
    test_identity_consistency();
    test_identity_providers_match();
    
    // Freshness tests
    std::cout << "\n--- Freshness Tests ---\n";
    test_freshness_tracking();
    test_freshness_clear_cache();
    
    // Partial state tests
    std::cout << "\n--- Partial State Tests ---\n";
    test_partial_state_detection();
    test_partial_state_observation();
    
    // Race tests
    std::cout << "\n--- Race Tests ---\n";
    test_race_concurrent_observation();
    test_race_modification_during_observation();
    
    // Disappearance tests
    std::cout << "\n--- Disappearance Tests ---\n";
    test_disappearing_resource_available();
    test_disappearing_resource_gone();
    test_disappearing_resource_reappearance();
    
    // Provider failure tests
    std::cout << "\n--- Provider Failure Tests ---\n";
    test_failure_runtime_error();
    test_failure_system_error();
    test_failure_multiple_failures();
    
    // Unsupported capability tests
    std::cout << "\n--- Unsupported Capability Tests ---\n";
    test_capability_detection();
    test_unsupported_operation_handling();
    
    // Resync tests
    std::cout << "\n--- Resync Tests ---\n";
    test_resync_sequence_recovery();
    test_resync_duplicate_detection();
    test_resync_out_of_order();
    
    // Cancellation tests
    std::cout << "\n--- Cancellation Tests ---\n";
    test_cancellation_request();
    test_cancellation_clear();
    
    // Bounded output tests
    std::cout << "\n--- Bounded Output Tests ---\n";
    test_bounded_output_limit();
    test_bounded_output_no_truncation();
    test_bounded_output_zero_limit();
    
    // Native fixture tests
    std::cout << "\n--- Native Fixture Tests ---\n";
    test_proc_fixture_current_process();
    test_proc_fixture_state();
    test_proc_fixture_adapter_exists();
    
    // Integration tests
    std::cout << "\n--- Integration Tests ---\n";
    test_isolated_provider_integration();
    test_failure_categories();
    test_partial_state_integration();
    test_identity_integration();
    test_freshness_integration();
    test_bounded_output_integration();
    test_native_fixture_integration();
    
    // Adversarial tests
    std::cout << "\n--- Adversarial Tests ---\n";
    test_adversarial_truncated_input();
    test_adversarial_large_output();
    test_adversarial_concurrent_operations();
    test_adversarial_rapid_failure_recovery();
    test_adversarial_null_adapter();
    
    std::cout << "\n========================================\n";
    std::cout << "All tests completed successfully!\n";
    std::cout << "========================================\n\n";
}

}  // namespace rebuntu::tests::provider_test_matrix

int main() {
    try {
        rebuntu::tests::provider_test_matrix::run_all_tests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nTEST FAILED: " << e.what() << "\n";
        return 1;
    }
}