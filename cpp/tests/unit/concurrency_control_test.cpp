// rebuntu::concurrency unit tests (Phase 6.31)
//
// Tests for narrow locking/serialization keyed by stable resource identity.

#include <gtest/gtest.h>
#include <system/concurrency/control.hpp>

TEST(ConcurrencyControlTest, ResourceIdEquality) {
    auto id1 = rebuntu::concurrency::ResourceId{"filesystem", "/etc/rebuntu.conf"};
    auto id2 = rebuntu::concurrency::ResourceId{"filesystem", "/etc/rebuntu.conf"};
    auto id3 = rebuntu::concurrency::ResourceId{"service", "nginx"};
    
    EXPECT_EQ(id1, id2);
    EXPECT_NE(id1, id3);
}

TEST(ConcurrencyControlTest, ResourceIdToString) {
    auto id = rebuntu::concurrency::ResourceId{"filesystem", "/etc/rebuntu.conf"};
    
    auto s = rebuntu::concurrency::to_string(id);
    EXPECT_EQ(s, "ResourceId{filesystem:/etc/rebuntu.conf}");
}

TEST(ConcurrencyControlTest, LockManagerAcquireAndRelease) {
    auto manager = rebuntu::concurrency::make_lock_manager();
    auto id = rebuntu::concurrency::ResourceId{"service", "nginx"};
    
    // First acquisition should succeed
    auto result1 = manager->acquire_lock(id, "exec-1");
    EXPECT_TRUE(result1.is_success());
    
    // Second acquisition by different executor should fail (non-blocking)
    auto result2 = manager->acquire_lock(id, "exec-2");
    EXPECT_FALSE(result2.is_success());
    EXPECT_TRUE(result2.is_blocked());
}

TEST(ConcurrencyControlTest, LockManagerMultipleResources) {
    auto manager = rebuntu::concurrency::make_lock_manager();
    
    auto id1 = rebuntu::concurrency::ResourceId{"service", "nginx"};
    auto id2 = rebuntu::concurrency::ResourceId{"service", "postgresql"};
    
    // Acquire lock on first resource
    auto result1 = manager->acquire_lock(id1, "exec-1");
    EXPECT_TRUE(result1.is_success());
    
    // Different resource should still be available
    auto result2 = manager->acquire_lock(id2, "exec-1");
    EXPECT_TRUE(result2.is_success());
}

TEST(ConcurrencyControlTest, LockManagerRelease) {
    auto manager = rebuntu::concurrency::make_lock_manager();
    auto id = rebuntu::concurrency::ResourceId{"service", "nginx"};
    
    // Acquire lock
    auto result1 = manager->acquire_lock(id, "exec-1");
    EXPECT_TRUE(result1.is_success());
    
    // Release lock
    manager->release_lock(id, "exec-1");
    
    // Should now be available for another executor
    auto result2 = manager->acquire_lock(id, "exec-2");
    EXPECT_TRUE(result2.is_success());
}

TEST(ConcurrencyControlTest, LockManagerIsLocked) {
    auto manager = rebuntu::concurrency::make_lock_manager();
    auto id = rebuntu::concurrency::ResourceId{"service", "nginx"};
    
    // Initially not locked
    EXPECT_FALSE(manager->is_resource_locked(id));
    
    // After acquire, should be locked
    manager->acquire_lock(id, "exec-1");
    EXPECT_TRUE(manager->is_resource_locked(id));
}

TEST(ConcurrencyControlTest, LockGuardRAII) {
    auto manager = rebuntu::concurrency::make_lock_manager();
    auto id = rebuntu::concurrency::ResourceId{"service", "nginx"};
    
    // Create LockGuard
    {
        auto guard = rebuntu::concurrency::LockGuard(manager, id, "exec-1");
        EXPECT_TRUE(guard.is_valid());
        
        // Resource should be locked while guard is in scope
        EXPECT_TRUE(manager->is_resource_locked(id));
    }
    
    // After guard goes out of scope, lock should be released
    EXPECT_FALSE(manager->is_resource_locked(id));
}

TEST(ConcurrencyControlTest, LockManagerMetrics) {
    auto manager = rebuntu::concurrency::make_lock_manager();
    auto id = rebuntu::concurrency::ResourceId{"service", "nginx"};
    
    // Initial metrics should be zero
    auto m = manager->metrics();
    EXPECT_EQ(m.total_acquisitions, 0u);
    EXPECT_EQ(m.successful_acquisitions, 0u);
    
    // Acquire a lock
    auto result1 = manager->acquire_lock(id, "exec-1");
    EXPECT_TRUE(result1.is_success());
    
    m = manager->metrics();
    EXPECT_EQ(m.total_acquisitions, 1u);
    EXPECT_EQ(m.successful_acquisitions, 1u);
}