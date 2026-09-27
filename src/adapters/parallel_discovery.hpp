// rebuntu::adapters::parallel_discovery — Bounded Parallel Discovery Infrastructure (Phase 5.51)
//
// This module provides bounded parallel discovery utilities for aggregating
// observations from multiple sources where beneficial.
//
// Design Principles:
//   - Parallelize only where independent work benefits from concurrency
//   - Never create unbounded thread-per-device patterns
//   - Deterministic shutdown with proper cancellation propagation
//   - Bounded concurrency using thread pools or worker sets
//   - Race-safe aggregation via thread-local results and final merge

#pragma once

#include "adapters/adapter_base.hpp"
#include "system/core/contracts.hpp"

#include <vector>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <thread>
#include <cstddef>
#include <string_view>

namespace rebuntu::adapters::parallel_discovery {

// ============================================================================
// ParallelDiscoveryOptions — Configuration for parallel discovery
//
// Controls the concurrency model:
//   - max_concurrent: Max workers/threads (bounded by hardware or policy)
//   - batch_size: How many items each worker processes before returning
//   - timeout_per_item: Per-item timeout (overall timeout is batched)
// ============================================================================
struct ParallelDiscoveryOptions {
    // Concurrency controls
    size_t max_concurrent = 4;                        // Max parallel workers
    size_t batch_size = 100;                          // Items per worker chunk
    
    // Timeout controls
    std::chrono::milliseconds timeout_per_item{500};  // Per-item timeout
    std::chrono::milliseconds overall_timeout{60000}; // Total operation timeout
    
    // Behavior controls
    bool stop_on_first_error = false;                  // Halt on first failure
    bool continue_on_partial_failure = true;           // Return partial results if some fail
};

// ============================================================================
// ParallelDiscoveryResult — Result of parallel discovery aggregation
//
// Carries aggregated observations with timing and error metadata.
// ============================================================================
template<typename T>
struct ParallelDiscoveryResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // Aggregated observations (successes only)
    std::vector<T> observations;
    
    // Timing information
    std::chrono::milliseconds elapsed_ms{0};
    size_t items_processed = 0;
    size_t items_failed = 0;
    
    // Error tracking (where not suppressed by continue_on_partial_failure)
    std::vector<std::pair<size_t, core::Error>> errors;  // index -> error mapping
    
    // Provenance
    std::string method{"parallel"};  // "parallel" or "sequential"
};

// ============================================================================
// WorkStealingQueue — Thread-safe work queue with work-stealing support
//
// Provides efficient parallel task distribution where workers can steal
// work from each other's queues when idle.
template<typename T>
class WorkStealingQueue {
public:
    WorkStealingQueue() = default;
    
    // Push item to this worker's queue (thread-safe)
    void push(T item) {
        std::lock_guard<std::mutex> lock(mutex_);
        local_queue_.push_back(std::move(item));
    }
    
    // Try to pop from this worker's queue
    bool try_pop(T& result) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (local_queue_.empty()) return false;
        result = std::move(local_queue_.front());
        local_queue_.pop_front();
        return true;
    }
    
    // Try to steal from another worker's queue
    bool try_steal(T& result) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (local_queue_.empty()) return false;
        // Steal from back (less critical)
        result = std::move(local_queue_.back());
        local_queue_.pop_back();
        return true;
    }
    
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return local_queue_.empty();
    }
    
private:
    mutable std::mutex mutex_;
    std::deque<T> local_queue_;
};

// ============================================================================
// WorkerPool — Bounded thread pool for parallel discovery
//
// Manages a fixed number of worker threads for bounded concurrency.
// Workers process tasks from shared work queue with optional work-stealing.
class WorkerPool : public adapters::CancellationState {
public:
    explicit WorkerPool(size_t num_workers = std::thread::hardware_concurrency())
        : num_workers_(std::max(size_t(1), std::min(num_workers, size_t(32)))) {}  // Cap at 32
    
    ~WorkerPool() {
        shutdown();
    }
    
    // Start worker threads
    void start() {
        if (running_) return;
        
        running_ = true;
        
        for (size_t i = 0; i < num_workers_; ++i) {
            workers_.emplace_back(&WorkerPool::run_worker, this, i);
        }
    }
    
    // Shutdown all workers gracefully
    void shutdown() {
        if (!running_) return;
        
        running_ = false;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            cv_.notify_all();
        }
        
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        
        workers_.clear();
    }
    
    // Submit a task to the pool
    template<typename Func>
    auto submit(Func func) -> std::future<decltype(func())> {
        using ResultType = decltype(func());
        
        auto task = std::make_shared<std::packaged_task<ResultType()>>(std::move(func));
        std::future<ResultType> result = task->get_future();
        
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!running_) {
                throw std::runtime_error("WorkerPool is not running");
            }
            tasks_.push([task]() { (*task)(); });
        }
        cv_.notify_one();
        
        return result;
    }
    
    // Wait for all pending tasks to complete
    void wait_for_all() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() {
            return tasks_.empty() && active_tasks_ == 0;
        });
    }
    
    // Check if pool is running
    bool is_running() const noexcept { return running_; }
    
    // Get number of workers
    size_t num_workers() const noexcept { return num_workers_; }
    
private:
    void run_worker(size_t worker_idx) {
        (void)worker_idx;  // Unused but could be used for affinity/affinity
        
        while (running_) {
            std::function<void()> task;
            
            {
                std::unique_lock<std::mutex> lock(mutex_);
                
                cv_.wait(lock, [this]() {
                    return !tasks_.empty() || !running_;
                });
                
                if (!running_ && tasks_.empty()) break;
                
                if (tasks_.empty()) continue;
                
                task = std::move(tasks_.front());
                tasks_.pop();
                active_tasks_++;
            }
            
            // Execute task
            try {
                if (task) task();
            } catch (...) {
                // Task exceptions are captured in the promise
            }
            
            {
                std::lock_guard<std::mutex> lock(mutex_);
                active_tasks_--;
                cv_.notify_all();
            }
        }
    }
    
    size_t num_workers_;
    bool running_{false};
    
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> tasks_;
    size_t active_tasks_{0};
    
    std::vector<std::thread> workers_;
};

// ============================================================================
// ParallelAggregator — Thread-safe result aggregation
//
// Aggregates results from parallel workers into a single collection.
template<typename T>
class ParallelAggregator {
public:
    explicit ParallelAggregator(size_t max_items = 10000)
        : max_items_(max_items), items_added_(0) {}
    
    // Add observations (thread-safe, bounded by max_items)
    bool add_observations(const std::vector<T>& obs) {
        if (!can_add(obs.size())) return false;
        
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& item : obs) {
            if (items_added_ >= max_items_) break;
            results_.push_back(item);
            items_added_++;
        }
        return true;
    }
    
    // Add a single observation
    bool add_observation(const T& item) {
        return add_observations(std::vector<T>{item});
    }
    
    // Record an error for a specific index
    void add_error(size_t index, const core::Error& error) {
        std::lock_guard<std::mutex> lock(mutex_);
        errors_.push_back({index, error});
    }
    
    // Get aggregated results (returns copy)
    std::vector<T> get_results() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return results_;
    }
    
    // Get errors
    std::vector<std::pair<size_t, core::Error>> get_errors() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return errors_;
    }
    
    // Check if we can add more items
    bool can_add(size_t count = 1) const noexcept {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex_));
        return (items_added_ + count) <= max_items_;
    }
    
    // Get total items added
    size_t total_items() const noexcept {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex_));
        return items_added_;
    }
    
private:
    mutable std::mutex mutex_;
    std::vector<T> results_;
    std::vector<std::pair<size_t, core::Error>> errors_;
    size_t max_items_;
    std::atomic<size_t> items_added_;
};

// ============================================================================
// ParallelDiscoveryEngine — Main engine for parallel discovery operations
//
// Manages bounded parallel discovery with proper cancellation propagation.
template<typename T>
class ParallelDiscoveryEngine {
public:
    using ResultType = ParallelDiscoveryResult<T>;
    
    explicit ParallelDiscoveryEngine(
        std::chrono::milliseconds default_timeout = std::chrono::seconds(30))
        : aggregator_(10000) {}  // Max 10k items
    
    ~ParallelDiscoveryEngine() {
        shutdown();
    }
    
    // Configure options
    void configure(const ParallelDiscoveryOptions& opts) {
        std::lock_guard<std::mutex> lock(options_mutex_);
        options_ = opts;
        
        // Recalculate workers based on hardware if auto
        if (options_.max_concurrent == 0) {
            options_.max_concurrent = std::thread::hardware_concurrency();
        }
    }
    
    // Start the engine
    void start() {
        shutdown();  // Ensure clean state
        
        pool_ = std::make_unique<WorkerPool>(options_.max_concurrent);
        pool_->start();
        
        aggregator_ = ParallelAggregator<T>(10000);
        cancelled_ = false;
    }
    
    // Shutdown all workers and cleanup
    void shutdown() {
        if (pool_) {
            pool_->shutdown();
            pool_.reset();
        }
    }
    
    // Check for cancellation before starting
    bool is_cancelled() const { return cancelled_; }
    
    // Request stop/cancellation
    void request_stop() { cancelled_ = true; }
    
    // Execute parallel discovery on a collection of items
    template<typename Item, typename ObserverFunc>
    ResultType execute_parallel(
        const std::vector<Item>& items,
        ObserverFunc observer) {
        
        record_operation_start();
        
        if (items.empty()) {
            return make_empty_result();
        }
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Check for cancellation before starting
        if (is_cancelled()) {
            return cancelled_result(start_time, "Discovery cancelled");
        }
        
        // Determine chunk size and number of chunks
        const size_t num_items = items.size();
        const size_t workers = std::min(
            options_.max_concurrent,
            std::max(size_t(1), num_items / options_.batch_size)
        );
        const size_t chunk_size = (num_items + workers - 1) / workers;  // Ceiling
        
        std::vector<std::future<void>> futures;
        
        // Submit chunks to worker pool
        for (size_t w = 0; w < workers && !is_cancelled(); ++w) {
            size_t start_idx = w * chunk_size;
            size_t end_idx = std::min(start_idx + chunk_size, num_items);
            
            if (start_idx >= end_idx) break;
            
            futures.push_back(pool_->submit([this, items, start_idx, end_idx,
                                            observer]() {
                process_chunk(items, start_idx, end_idx, observer);
            }));
        }
        
        // Wait for all workers to complete
        for (auto& f : futures) {
            try {
                f.get();
            } catch (...) {
                // Exceptions from workers are caught
            }
        }
        
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time);
        
        // Check overall timeout
        if (is_past_deadline()) {
            return TimeoutResult<T>::timeout(
                "Discovery exceeded overall timeout",
                elapsed);
        }
        
        // Collect results
        auto results = aggregator_.get_results();
        auto errors = aggregator_.get_errors();
        
        ResultType result;
        result.observations = std::move(results);
        result.errors = std::move(errors);
        result.elapsed_ms = elapsed;
        result.items_processed = items.size();
        result.items_failed = errors.size();
        result.status = result.items_failed == 0
            ? core::SemanticStatus::kCompleted
            : (options_.continue_on_partial_failure 
               ? core::SemanticStatus::kCompleted
               : core::SemanticStatus::kFailure);
        
        return result;
    }
    
    // Sequential fallback for when parallel is not beneficial
    template<typename Item, typename ObserverFunc>
    ResultType execute_sequential(
        const std::vector<Item>& items,
        ObserverFunc observer) {
        
        record_operation_start();
        auto start_time = std::chrono::steady_clock::now();
        
        if (items.empty()) {
            return make_empty_result();
        }
        
        std::vector<T> results;
        size_t failed_count = 0;
        
        for (size_t i = 0; i < items.size() && !is_cancelled(); ++i) {
            try {
                auto item_result = observer(items[i]);
                
                // If the observer returns something with a status field
                if constexpr (requires { item_result.status; }) {
                    if (item_result.status == core::SemanticStatus::kSuccess ||
                        item_result.status == core::SemanticStatus::kCompleted) {
                        
                        // Extract actual observation from result
                        if constexpr (requires { item_result.value; }) {
                            if (item_result.value.has_value()) {
                                results.push_back(*item_result.value);
                            }
                        } else {
                            // If observer returns T directly
                            results.push_back(item_result);
                        }
                    } else {
                        failed_count++;
                        if (!options_.continue_on_partial_failure) {
                            break;
                        }
                    }
                } else {
                    // Observer returns T directly - always succeed
                    results.push_back(item_result);
                }
            } catch (const std::exception& e) {
                failed_count++;
                if (!options_.continue_on_partial_failure) {
                    break;
                }
            }
            
            // Check per-item timeout
            if (is_past_deadline()) {
                break;
            }
        }
        
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time);
        
        ResultType result;
        result.observations = std::move(results);
        result.elapsed_ms = elapsed;
        result.items_processed = items.size();
        result.items_failed = failed_count;
        result.method = "sequential";
        result.status = (failed_count == 0)
            ? core::SemanticStatus::kCompleted
            : (options_.continue_on_partial_failure
               ? core::SemanticStatus::kCompleted
               : core::SemanticStatus::kFailure);
        
        return result;
    }
    
private:
    void record_operation_start() {
        // Record operation start time for timeout tracking
        operation_start_ = std::chrono::steady_clock::now();
    }
    
    bool is_past_deadline() const {
        if (options_.overall_timeout.count() <= 0) return false;
        auto elapsed = std::chrono::steady_clock::now() - operation_start_;
        return elapsed > options_.overall_timeout;
    }
    
    template<typename Item>
    void process_chunk(
        const std::vector<Item>& items,
        size_t start_idx,
        size_t end_idx,
        std::function<T(const Item&)> observer) {
        
        for (size_t i = start_idx; i < end_idx && !cancelled_; ++i) {
            if (!aggregator_.can_add()) break;
            
            try {
                T item_result = observer(items[i]);
                
                // Observer returns T directly
                aggregator_.add_observation(item_result);
            } catch (const std::exception& e) {
                core::Error err{"E_PARALLEL_WORKER", e.what()};
                aggregator_.add_error(i, err);
                
                if (options_.stop_on_first_error) {
                    cancelled_ = true;
                    break;
                }
            }
        }
    }
    
    ResultType make_empty_result() {
        ResultType result;
        result.status = core::SemanticStatus::kCompleted;
        return result;
    }
    
    template<typename Clock, typename Duration>
    ResultType cancelled_result(
        std::chrono::time_point<Clock, Duration> start_time,
        std::string_view reason) {
        
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time);
        
        ResultType result;
        result.status = core::SemanticStatus::kCancelled;
        result.elapsed_ms = elapsed;
        return result;
    }
    
    ParallelDiscoveryOptions options_;
    mutable std::mutex options_mutex_;
    
    std::unique_ptr<WorkerPool> pool_;
    ParallelAggregator<T> aggregator_;
    mutable std::mutex cancel_mutex_;
    bool cancelled_{false};
    std::chrono::steady_clock::time_point operation_start_;
};

// ============================================================================
// ParallelDiscoveryEngineFactory — Factory for creating parallel discovery engines
//
// Provides convenient construction with default settings.
class ParallelDiscoveryEngineFactory {
public:
    // Create a new engine with specified options
    template<typename T>
    static std::unique_ptr<ParallelDiscoveryEngine<T>> create(
        const ParallelDiscoveryOptions& opts = {}) {
        
        auto engine = std::make_unique<ParallelDiscoveryEngine<T>>();
        engine->configure(opts);
        return engine;
    }
    
    // Create a default engine with sensible defaults
    template<typename T>
    static std::unique_ptr<ParallelDiscoveryEngine<T>> create_default() {
        ParallelDiscoveryOptions opts;
        opts.max_concurrent = 0;  // Auto-detect hardware concurrency
        opts.batch_size = 100;
        opts.timeout_per_item = std::chrono::milliseconds(500);
        opts.overall_timeout = std::chrono::milliseconds(60000);
        opts.stop_on_first_error = false;
        opts.continue_on_partial_failure = true;
        
        return create<T>(opts);
    }
};

}  // namespace rebuntu::adapters::parallel_discovery