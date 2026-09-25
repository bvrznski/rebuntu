// rebuntu::test_journal_normalizer — Unit Tests for Journal Normalizer (Phase 5.3)
//
// Tests filter decisions, deduplication, noise suppression,
// and normalization of journal records.

#include "adapters/journal_normalizer.hpp"

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

namespace rebuntu::adapters {

// ============================================================================
// NoisePattern tests
// ============================================================================

TEST(JournalNormalizerTest, NoisePatternExactMatch) {
    NoisePattern p{"test", "exact_match", "hello"};
    
    EXPECT_TRUE(p.matches("hello"));
    EXPECT_FALSE(p.matches("Hello"));  // Case sensitive
    EXPECT_FALSE(p.matches("hello world"));
}

TEST(JournalNormalizerTest, NoisePatternPrefix) {
    NoisePattern p{"test", "prefix", "Systemd"};
    
    EXPECT_TRUE(p.matches("Systemd service started"));
    EXPECT_FALSE(p.matches("systemd service started"));  // Case sensitive
    EXPECT_FALSE(p.matches("my Systemd"));
}

TEST(JournalNormalizerTest, NoisePatternContains) {
    NoisePattern p{"test", "contains", "error"};
    
    EXPECT_TRUE(p.matches("service error occurred"));
    EXPECT_TRUE(p.matches("error"));
    EXPECT_FALSE(p.matches("success"));
}

// ============================================================================
// JournalDeduplicationCache tests
// ============================================================================

TEST(JournalNormalizerTest, DeduplicationCacheNewEntry) {
    JournalDeduplicationCache cache(std::chrono::seconds(5), 100);
    
    EXPECT_FALSE(cache.is_duplicate("unique-fingerprint-1"));
}

TEST(JournalNormalizerTest, DeduplicationCacheDuplicateDetection) {
    JournalDeduplicationCache cache(std::chrono::seconds(5), 100);
    
    // First occurrence - not a duplicate
    EXPECT_FALSE(cache.is_duplicate("fingerprint-a"));
    cache.record_event("fingerprint-a");
    
    // Second occurrence within window - is a duplicate
    EXPECT_TRUE(cache.is_duplicate("fingerprint-a"));
}

TEST(JournalNormalizerTest, DeduplicationCacheWindowExpiration) {
    JournalDeduplicationCache cache(std::chrono::milliseconds(50), 100);
    
    cache.record_event("fingerprint-b");
    
    // Should be duplicate immediately after recording
    EXPECT_TRUE(cache.is_duplicate("fingerprint-b"));
    
    // Wait for window to expire
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    
    // Cleanup should remove expired entry
    size_t removed = cache.cleanup(std::chrono::system_clock::now());
    EXPECT_GE(removed, 1u);
    
    // Now it's not a duplicate anymore
    EXPECT_FALSE(cache.is_duplicate("fingerprint-b"));
}

TEST(JournalNormalizerTest, DeduplicationCacheStatistics) {
    JournalDeduplicationCache cache(std::chrono::seconds(5), 100);
    
    // Record some events
    for (int i = 0; i < 5; ++i) {
        cache.record_event("fingerprint-" + std::to_string(i));
    }
    
    auto stats = cache.statistics();
    EXPECT_EQ(stats.total_events, 5u);
}

TEST(JournalNormalizerTest, DeduplicationCacheEvictionAtCapacity) {
    JournalDeduplicationCache cache(std::chrono::seconds(5), 3);
    
    // Fill to capacity
    cache.record_event("a");
    cache.record_event("b");
    cache.record_event("c");
    
    auto stats = cache.statistics();
    EXPECT_EQ(stats.unique_events, 3u);
}

// ============================================================================
// JournalNoiseFilter tests
// ============================================================================

TEST(JournalNormalizerTest, NoiseFilterDetectsSystemdNoise) {
    const std::vector<std::string> noise_messages = {
        "Received SIGCHLD",
        "Child exited",
        "State changed to running",
        "Reloading configuration",
        "Got message from client",
    };
    
    for (const auto& msg : noise_messages) {
        EXPECT_TRUE(JournalNoiseFilter::is_noise(msg))
            << "Expected '" << msg << "' to be detected as noise";
    }
}

TEST(JournalNormalizerTest, NoiseFilterDetectsKernelNoise) {
    const std::vector<std::string> kernel_noise = {
        "[    0.000000] CPU0: Core temperature above threshold",
        "DMI: System manufacturer Product Name",
        "ACPI: PCI Interrupt Link [LNKA] enabled at IRQ 11",
        "pci 0000:00:1f.2: reg 0x10: IO bars",
        "Memory: 8000000K/8000000K available",
    };
    
    for (const auto& msg : kernel_noise) {
        EXPECT_TRUE(JournalNoiseFilter::is_noise(msg))
            << "Expected '" << msg << "' to be detected as kernel noise";
    }
}

TEST(JournalNormalizerTest, NoiseFilterAllowsInterestingMessages) {
    const std::vector<std::string> interesting = {
        "Critical: Service failed",
        "ERROR: Disk I/O error on /dev/sda1",
        "Warning: High CPU usage detected",
        "User login successful",
    };
    
    for (const auto& msg : interesting) {
        EXPECT_FALSE(JournalNoiseFilter::is_noise(msg))
            << "Expected '" << msg << "' NOT to be detected as noise";
    }
}

// ============================================================================
// JournalEventFilter tests
// ============================================================================

TEST(JournalNormalizerTest, FilterConfigDefaults) {
    JournalFilterConfig config;
    
    EXPECT_EQ(config.min_priority, std::nullopt);
    EXPECT_TRUE(config.include_units.empty());
    EXPECT_TRUE(config.exclude_units.empty());
    EXPECT_EQ(config.max_evidence_per_record, 16u);
}

TEST(JournalNormalizerTest, PriorityFilterAllowsHighPriority) {
    JournalFilterConfig config;
    config.min_priority = 3;  // Include priority <= 3 (errors)
    
    runtime::Event event;
    event.source = "journald";
    event.type = "error";
    
    core::Evidence e;
    e.source = "journal_message";
    e.value = "PRIORITY=2";  // Error level
    event.evidence.push_back(e);
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    FilterDecision decision = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision, FilterDecision::kAllow)
        << "Error-level record should be allowed with min_priority=3";
}

TEST(JournalNormalizerTest, PriorityFilterBlocksLowPriority) {
    JournalFilterConfig config;
    config.min_priority = 4;  // Include priority <= 4 (warnings and above)
    
    runtime::Event event;
    event.source = "journald";
    event.type = "info";
    
    core::Evidence e;
    e.source = "journal_message";
    e.value = "PRIORITY=6";  // Info level
    event.evidence.push_back(e);
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    FilterDecision decision = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision, FilterDecision::kSuppressFilter)
        << "Info-level record should be filtered with min_priority=4";
}

TEST(JournalNormalizerTest, UnitIncludeFilter) {
    JournalFilterConfig config;
    config.include_units = {"ssh.service", "sshd.service"};
    
    runtime::Event event;
    event.source = "journald";
    
    core::Evidence e1;
    e1.source = "journal_unit";
    e1.value = "_SYSTEMD_UNIT=ssh.service";
    event.evidence.push_back(e1);
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    FilterDecision decision = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision, FilterDecision::kAllow)
        << " ssh.service should pass include filter";
}

TEST(JournalNormalizerTest, UnitExcludeFilter) {
    JournalFilterConfig config;
    config.exclude_units = {"systemd-journald"};
    
    runtime::Event event;
    event.source = "journald";
    
    core::Evidence e1;
    e1.source = "journal_unit";
    e1.value = "_SYSTEMD_UNIT=systemd-journald";
    event.evidence.push_back(e1);
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    FilterDecision decision = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision, FilterDecision::kSuppressFilter)
        << " systemd-journald should be excluded";
}

TEST(JournalNormalizerTest, NoiseRecordSuppressed) {
    JournalFilterConfig config;
    
    runtime::Event event;
    event.source = "journald";
    
    core::Evidence e1;
    e1.source = "journal_message";
    e1.value = "Received SIGCHLD child 1234 exited";
    event.evidence.push_back(e1);
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    FilterDecision decision = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision, FilterDecision::kSuppressNoise)
        << " SIGCHLD message should be suppressed as noise";
}

TEST(JournalNormalizerTest, DeduplicationSuppression) {
    JournalFilterConfig config;
    
    runtime::Event event;
    event.source = "journald";
    
    core::Evidence e1;
    e1.source = "journal_message";
    e1.value = "Important error message";
    event.evidence.push_back(e1);
    
    bool first_seen = false;
    bool second_seen = false;
    
    JournalEventFilter filter(config, 
        [&](const NormalizedEvent& n) { 
            if (!first_seen) first_seen = true; 
            else second_seen = true;
        });
    
    // First occurrence
    auto decision1 = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision1, FilterDecision::kAllow);
    
    // Second occurrence (same content) - should be suppressed
    auto decision2 = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision2, FilterDecision::kSuppressDuplicate)
        << " Duplicate record should be suppressed";
}

TEST(JournalNormalizerTest, NormalizedEventPreservesEvidence) {
    JournalFilterConfig config;
    
    runtime::Event event;
    event.source = "journald";
    event.type = "error";
    event.id = "test-event-123";
    
    core::Evidence e1;
    e1.source = "journal_message";
    e1.value = "PRIORITY=0 Message text";
    event.evidence.push_back(e1);
    
    core::Evidence e2;
    e2.source = "journal_unit";
    e2.value = "_SYSTEMD_UNIT=test.service";
    event.evidence.push_back(e2);
    
    NormalizedEvent saved_event;
    JournalEventFilter filter(config, 
        [&](const NormalizedEvent& n) { saved_event = n; });
    
    auto decision = filter.process_record(event, std::chrono::system_clock::now());
    EXPECT_EQ(decision, FilterDecision::kAllow);
    
    // Verify normalization occurred
    EXPECT_EQ(saved_event.event.source, "journald");
    EXPECT_EQ(saved_event.original_evidence.size(), 2u);
    EXPECT_FALSE(saved_event.journal_cursor.empty() || saved_event.boot_id.empty())
        << " Normalized event should have source identifiers";
}

TEST(JournalNormalizerTest, FilterMetricsAreTracked) {
    JournalFilterConfig config;
    
    runtime::Event normal_event;
    normal_event.source = "journald";
    
    core::Evidence e1;
    e1.source = "journal_message";
    e1.value = "Some interesting message";
    normal_event.evidence.push_back(e1);
    
    runtime::Event noise_event;
    noise_event.source = "journald";
    
    core::Evidence e2;
    e2.source = "journal_message";
    e2.value = "Received SIGCHLD";
    noise_event.evidence.push_back(e2);
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    // Process events
    filter.process_record(normal_event, std::chrono::system_clock::now());
    filter.process_record(noise_event, std::chrono::system_clock::now());
    filter.process_record(normal_event, std::chrono::system_clock::now());  // Will be duplicate
    
    auto metrics = filter.metrics();
    
    EXPECT_EQ(metrics.records_received, 3u);
    EXPECT_EQ(metrics.records_normalized, 1u);  // Only the first normal event
    EXPECT_GE(metrics.records_suppressed_noise + metrics.records_dropped_duplicate, 1u);
}

TEST(JournalNormalizerTest, BatchProcessing) {
    JournalFilterConfig config;
    
    std::vector<runtime::Event> events;
    for (int i = 0; i < 5; ++i) {
        runtime::Event event;
        event.source = "journald";
        
        core::Evidence e;
        e.source = "journal_message";
        e.value = "Batch message " + std::to_string(i);
        event.evidence.push_back(e);
        
        events.push_back(event);
    }
    
    JournalEventFilter filter(config, [](const NormalizedEvent&) {});
    
    size_t processed = filter.process_batch(events, std::chrono::system_clock::now());
    
    EXPECT_EQ(processed, 5u);
}

// ============================================================================
// Factory function test
// ============================================================================

TEST(JournalNormalizerTest, FactoryCreatesValidFilter) {
    auto filter = make_journal_filter(
        JournalFilterConfig{},
        [](const NormalizedEvent&) {});
    
    EXPECT_NE(filter, nullptr);
    EXPECT_FALSE(filter->is_running());
}

}  // namespace rebuntu::adapters

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}