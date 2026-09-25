// Rebuntu Phase 5.1 Event Collector Tests
//
// Test suite for the System Event Collector implementation.

#include <gtest/gtest.h>
#include "events/collector.hpp"

namespace rebuntu::events {

// ============================================================================
// InMemoryEventChannel Tests
// ============================================================================

TEST(InMemoryEventChannelTest, PublishAndReceive) {
    auto channel = make_event_channel(10);
    
    runtime::Event event;
    event.id = "test-1";
    event.source = "inotify";
    event.type = "file-created";
    
    EXPECT_TRUE(channel->publish(event));
    EXPECT_EQ(channel->queue_depth(), 1);
    
    auto received = channel->receive(std::chrono::milliseconds(0));
    EXPECT_TRUE(received.has_value());
    EXPECT_EQ(received->id, "test-1");
}

TEST(InMemoryEventChannelTest, QueueFullDropNewest) {
    auto channel = make_event_channel(2);
    
    runtime::Event event1;
    event1.id = "test-1";
    
    runtime::Event event2;
    event2.id = "test-2";
    
    runtime::Event event3;
    event3.id = "test-3";
    
    EXPECT_TRUE(channel->publish(event1));
    EXPECT_TRUE(channel->publish(event2));
    
    // Channel is now full, should drop newest
    EXPECT_FALSE(channel->publish(event3));
}

TEST(InMemoryEventChannelTest, ClosePreventsPublish) {
    auto channel = make_event_channel(10);
    
    channel->close();
    EXPECT_FALSE(channel->publish({}));
}

TEST(EventNormalizerTest, ParseSystemdStateChange) {
    auto timestamp = std::chrono::system_clock::now();
    
    auto event = EventNormalizer::parse_systemd_state_change(
        "nginx.service", 
        "active", 
        timestamp);
    
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(event->source, "systemd");
    EXPECT_EQ(event->type, "active");
    EXPECT_EQ(event->subject, "nginx.service");
}

TEST(EventNormalizerTest, ParseUdevEvent) {
    auto timestamp = std::chrono::system_clock::now();
    
    std::unordered_map<std::string, std::string> env;
    env["DEVNAME"] = "/dev/sda1";
    env["SUBSYSTEM"] = "block";
    
    auto event = EventNormalizer::parse_udev_event("add", env, timestamp);
    
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(event->source, "udev");
    EXPECT_EQ(event->type, "add");
}

TEST(EventNormalizerTest, ParseFilesystemEvent) {
    auto timestamp = std::chrono::system_clock::now();
    
    auto event = EventNormalizer::parse_filesystem_event(
        42,
        IN_CREATE | IN_MODIFY,
        "/tmp/testfile",
        timestamp);
    
    ASSERT_TRUE(event.has_value());
    EXPECT_EQ(event->source, "inotify");
}

}  // namespace rebuntu::events