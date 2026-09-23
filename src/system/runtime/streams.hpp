// rebuntu::runtime::stream — Stream with backpressure (Phase 0.15)
//
// Defines Stream as an ordered sequence of items with bounded buffering
// and explicit backpressure handling.

#pragma once

#include <system/core/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime::stream {

enum class BackpressurePolicy {
    kBlock,        // Producer blocks when buffer full
    kDropNewest,   // Drop new items when buffer full
    kDropOldest,   // Drop oldest items when buffer full (circular buffer)
};

struct BufferConfig {
    size_t max_size = 1024;
    BackpressurePolicy policy = BackpressurePolicy::kBlock;
};

class StreamConsumer {
public:
    virtual ~StreamConsumer() = default;
    
    // Called when a new item is available
    virtual void on_item(std::string item) = 0;
    
    // Called when stream completes
    virtual void on_complete() = 0;
    
    // Called on error
    virtual void on_error(const core::Error& err) = 0;
};

class StreamProducer {
public:
    virtual ~StreamProducer() = default;
    
    // Produce next item, returns nullopt if exhausted
    virtual std::optional<std::string> next() = 0;
    
    // Check if more items available
    virtual bool has_next() const = 0;
};

// Bounded stream with explicit backpressure handling
class BoundedStream {
public:
    BoundedStream(BufferConfig config);
    
    // Produce an item, returns false if dropped/backpressure applied
    bool produce(std::string item);
    
    // Consume next item, blocks until available or timeout
    std::optional<std::string> consume(std::chrono::milliseconds timeout);
    
    // Get current buffer size
    size_t buffer_size() const;
    
    // Check if buffer is full
    bool is_full() const;
    
    // Close the stream (no more produces)
    void close();

private:
    BufferConfig config_;
    std::vector<std::string> buffer_;
    size_t head_ = 0;   // Next to consume
    size_t tail_ = 0;   // Next position to write
    bool closed_ = false;
};

// Coalescing stream: merges rapid items into single notification
class CoalescingStream {
public:
    explicit CoalescingStream(std::chrono::milliseconds window);
    
    bool produce(std::string item);
    std::optional<std::string> consume(std::chrono::milliseconds timeout);

private:
    std::chrono::milliseconds window_;
    std::vector<std::string> buffer_;
};

}  // namespace rebuntu::runtime::stream
