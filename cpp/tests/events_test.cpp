// Test file for Phase 0.15 - Events, Signals, Requests, Messages & Communication

#include <runtime/ipc.hpp>
#include <events/in_memory_channel.hpp>
#include <runtime/core/contracts.hpp>
#include <cassert>
#include <chrono>
#include <thread>
#include <iostream>

using namespace rebuntu::runtime;
using namespace rebuntu::events;

void test_message_creation() {
    // Test Message creation
    ipc::Message msg;
    msg.kind = ipc::MessageKind::kRequest;
    msg.id = "test-request-1";
    
    assert(msg.kind == ipc::MessageKind::kRequest);
    std::cout << "test_message_creation: PASSED" << std::endl;
}

void test_in_memory_channel_send_receive() {
    // Test basic send/receive
    ipc::ChannelOptions opts;
    opts.max_buffer_size = 10;
    
    InMemoryChannel channel(opts);
    ipc::Message msg;
    msg.kind = ipc::MessageKind::kEvent;
    msg.id = "event-1";
    
    bool sent = channel.send(msg);
    assert(sent == true);
    assert(channel.queue_size() == 1);
    
    auto received = channel.receive(std::chrono::milliseconds(100));
    assert(received.has_value());
    assert(received->id == "event-1");
    assert(channel.queue_size() == 0);
    
    std::cout << "test_in_memory_channel_send_receive: PASSED" << std::endl;
}

void test_in_memory_channel_timeout() {
    // Test receive timeout
    InMemoryChannel channel;
    
    auto result = channel.receive(std::chrono::milliseconds(50));
    assert(!result.has_value());
    
    std::cout << "test_in_memory_channel_timeout: PASSED" << std::endl;
}

void test_backpressure_drop_oldest() {
    // Test backpressure policy - drop oldest
    ipc::ChannelOptions opts;
    opts.max_buffer_size = 3;
    opts.backpressure = ipc::BackpressurePolicy::kDropOldest;
    
    InMemoryChannel channel(opts);
    
    for (int i = 0; i < 5; ++i) {
        ipc::Message msg;
        msg.id = "msg-" + std::to_string(i);
        channel.send(msg);
    }
    
    // Queue should have max_buffer_size items
    assert(channel.queue_size() == 3);
    
    std::cout << "test_backpressure_drop_oldest: PASSED" << std::endl;
}

void test_has_ready() {
    // Test has_ready before and after receiving
    InMemoryChannel channel;
    
    assert(channel.has_ready() == false);
    
    ipc::Message msg;
    msg.id = "test";
    channel.send(msg);
    
    assert(channel.has_ready() == true);
    
    auto _ = channel.receive(std::chrono::milliseconds(10));
    
    assert(channel.has_ready() == false);
    
    std::cout << "test_has_ready: PASSED" << std::endl;
}

void test_close() {
    // Test closing the channel
    InMemoryChannel channel;
    
    ipc::Message msg;
    msg.id = "final";
    channel.send(msg);
    
    channel.close();
    
    // Should still be able to receive existing messages after close
    auto msg1 = channel.receive(std::chrono::milliseconds(10));
    assert(msg1.has_value());
    
    // New receive should return empty after queue exhausted
    auto msg2 = channel.receive(std::chrono::milliseconds(10));
    assert(!msg2.has_value());
    
    std::cout << "test_close: PASSED" << std::endl;
}

void test_correlation_ids() {
    // Test CorrelationIds structure
    ipc::CorrelationIds corr;
    corr.request_id = "req-1";
    corr.correlation_id = "corr-1";
    corr.causation_id = "cause-1";
    
    assert(corr.request_id == "req-1");
    assert(corr.correlation_id.has_value());
    
    std::cout << "test_correlation_ids: PASSED" << std::endl;
}

void test_message_kinds() {
    // Test MessageKind enum values
    assert(ipc::to_string(ipc::MessageKind::kEvent) == "event");
    assert(ipc::to_string(ipc::MessageKind::kRequest) == "request");
    assert(ipc::to_string(ipc::MessageKind::kResponse) == "response");
    assert(ipc::to_string(ipc::MessageKind::kCommand) == "command");
    
    std::cout << "test_message_kinds: PASSED" << std::endl;
}

void test_backpressure_policies() {
    // Test BackpressurePolicy enum values
    using bp = ipc::BackpressurePolicy;
    assert(ipc::to_string(bp::kBlock) == "block");
    assert(ipc::to_string(bp::kDropNewest) == "drop_newest");
    assert(ipc::to_string(bp::kDropOldest) == "drop_oldest");
    
    std::cout << "test_backpressure_policies: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Phase 0.15 communication grammar tests..." << std::endl;
    
    test_message_creation();
    test_in_memory_channel_send_receive();
    test_in_memory_channel_timeout();
    test_backpressure_drop_oldest();
    test_has_ready();
    test_close();
    test_correlation_ids();
    test_message_kinds();
    test_backpressure_policies();
    
    std::cout << "All tests PASSED!" << std::endl;
    return 0;
}