// rebuntu::events::InMemoryChannel — In-process communication channel (Phase 0.15)
//
// Implements a thread-safe, bounded queue for in-process message passing.
// Uses std::condition_variable for efficient blocking receive operations.

#pragma once

#include <runtime/ipc.hpp>
#include <runtime/core/result.hpp>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <optional>

namespace rebuntu::events {

class InMemoryChannel : public runtime::ipc::Channel {
public:
    explicit InMemoryChannel(runtime::ipc::ChannelOptions options = {})
        : options_(std::move(options)) {}

    // Send a message to the channel
    bool send(runtime::ipc::Message msg) override {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Apply backpressure policy when queue is full
        if (queue_.size() >= options_.max_buffer_size) {
            switch (options_.backpressure) {
                case runtime::ipc::BackpressurePolicy::kBlock:
                    return false;  // Block until space available
                case runtime::ipc::BackpressurePolicy::kDropNewest:
                    return false;  // Drop the newest message
                case runtime::ipc::BackpressurePolicy::kDropOldest:
                    queue_.pop();  // Remove oldest and add new
                    break;
            }
        }
        
        queue_.push(std::move(msg));
        cv_.notify_one();
        return true;
    }

    // Receive a message with optional timeout
    std::optional<runtime::ipc::Message> receive(std::chrono::milliseconds timeout) override {
        std::unique_lock<std::mutex> lock(mutex_);
        
        if (!cv_.wait_for(lock, timeout, [this] { 
            return !queue_.empty() || closed_; 
        })) {
            return std::nullopt;  // Timeout
        }
        
        if (closed_ && queue_.empty()) {
            return std::nullopt;  // Channel closed
        }
        
        runtime::ipc::Message msg = std::move(queue_.front());
        queue_.pop();
        return msg;
    }

    // Check if there are messages ready to receive
    bool has_ready() const override {
        std::lock_guard<std::mutex> lock(mutex_);
        return !queue_.empty();
    }

    // Close the channel (signals all waiting receivers)
    void close() override {
        std::lock_guard<std::mutex> lock(mutex_);
        closed_ = true;
        cv_.notify_all();
    }

    // Get current queue size
    size_t queue_size() const override {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    runtime::ipc::ChannelOptions options_;
    mutable std::mutex mutex_;
    std::queue<runtime::ipc::Message> queue_;
    std::condition_variable cv_;
    bool closed_ = false;
};

}  // namespace rebuntu::events