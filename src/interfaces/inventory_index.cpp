// rebuntu::interfaces::inventory_index — Inventory Indexing Implementation (Phase 5.45)
//
// This module provides a concrete implementation of the inventory indexer
// interface that follows Rebuntu's key invariants:
//
//   - INDEXES ARE DERIVED: Indexes are rebuildable views from authoritative source data
//   - INDEXES ARE NON-AUTHORITATIVE: Source truth always overrides index state
//   - ABSENCE IS UNKNOWN: Missing index entry means "not found in index", not "does not exist"

#include "inventory_index.hpp"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>

namespace rebuntu::interfaces {

// ============================================================================
// InventoryIndexerImpl — Concrete implementation
// ============================================================================
class InventoryIndexerImpl : public InventoryIndexer {
public:
    InventoryIndexerImpl() = default;
    
    core::Outcome configure(std::chrono::milliseconds stale_threshold,
                           size_t max_entries_per_index) override {
        stale_threshold_ = stale_threshold;
        max_entries_per_index_ = max_entries_per_index;
        return core::Outcome::success();
    }
    
    core::Outcome start() override {
        is_running_.store(true);
        return core::Outcome::success();
    }
    
    core::Outcome stop() override {
        is_running_.store(false);
        return core::Outcome::success();
    }
    
    IndexBuildResult build(const IndexBuildRequest& request) override {
        IndexBuildResult result;
        
        if (!is_running_.load()) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Indexer is not running";
            return result;
        }
        
        result.build_request_id = request.id;
        result.started_at = std::chrono::system_clock::now();
        
        // Build each requested index kind
        std::vector<IndexKind> kinds_to_build;
        if (request.kinds.has_value()) {
            kinds_to_build = *request.kinds;
        } else {
            kinds_to_build.push_back(IndexKind::kByName);
            kinds_to_build.push_back(IndexKind::kByType);
            kinds_to_build.push_back(IndexKind::kByLocation);
            kinds_to_build.push_back(IndexKind::kByTag);
            kinds_to_build.push_back(IndexKind::kByState);
        }
        
        for (auto kind : kinds_to_build) {
            // Build the index for this kind
            size_t entries = build_index_for_kind(kind, request.max_entries);
            result.entries_built += entries;
            result.indexes_rebuilt++;
            
            // Track errors encountered during build
            if (entries >= request.max_entries) {
                core::Error err{"E_INDEX_TRUNCATED", "Index truncated at max_entries limit"};
                result.errors.emplace_back(EntityId(), err);
            }
        }
        
        result.completed_at = std::chrono::system_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            result.completed_at - result.started_at
        );
        result.status = core::SemanticStatus::kCompleted;
        result.description = "Inventory index rebuild completed";
        
        return result;
    }
    
    bool is_index_stale(IndexKind kind, std::chrono::milliseconds threshold) const override {
        auto it = freshness_timestamps_.find(kind);
        if (it == freshness_timestamps_.end()) {
            // No index exists yet - considered "stale" in the sense that we need to build it
            return true;
        }
        
        auto now = std::chrono::system_clock::now();
        auto elapsed = now - it->second;
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        
        return elapsed_ms > threshold;
    }
    
    IndexQueryResult query_by_id(const EntityId& id) override {
        IndexQueryResult result;
        result.status = core::SemanticStatus::kUnknown;
        result.found = false;
        
        if (!is_running_.load()) {
            result.status = core::SemanticStatus::kFailure;
            return result;
        }
        
        auto start_time = std::chrono::system_clock::now();
        
        // First check the index
        auto it = by_id_index_.find(id.value);
        if (it != by_id_index_.end()) {
            auto end_time = std::chrono::system_clock::now();
            result.index_lookup_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            );
            
            result.found = true;
            result.entity_id = id;  // Use the passed EntityId directly
            result.source = IndexQueryResult::Source::kIndex;
            result.status = core::SemanticStatus::kCompleted;
            
            // Record evidence that this was found via index lookup
            core::Evidence ev;
            ev.source = "inventory-index";
            ev.value = "index-lookup: entity_id=" + id.value;
            ev.captured_at = format_timestamp(end_time);
            result.evidence.push_back(ev);
        } else {
            // Not in index - this does NOT mean the entity doesn't exist!
            auto end_time = std::chrono::system_clock::now();
            result.index_lookup_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            );
            
            result.status = core::SemanticStatus::kUnknown;
            
            // Record evidence that entity was not in index (not authoritative absence!)
            core::Evidence ev;
            ev.source = "inventory-index";
            ev.value = "index-miss: entity_id=" + id.value;
            ev.captured_at = format_timestamp(end_time);
            result.evidence.push_back(ev);
        }
        
        return result;
    }
    
    IndexQueryResult query_by_name(std::string_view name) override {
        IndexQueryResult result;
        result.status = core::SemanticStatus::kUnknown;
        result.found = false;
        
        if (!is_running_.load()) {
            result.status = core::SemanticStatus::kFailure;
            return result;
        }
        
        auto start_time = std::chrono::system_clock::now();
        
        // Check name index
        auto it = by_name_index_.find(std::string{name});
        if (it != by_name_index_.end()) {
            auto end_time = std::chrono::system_clock::now();
            result.index_lookup_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            );
            
            result.found = true;
            result.entity_id = EntityId{it->second};
            result.source = IndexQueryResult::Source::kIndex;
            result.status = core::SemanticStatus::kCompleted;
            
            // Record evidence
            core::Evidence ev;
            ev.source = "inventory-index";
            ev.value = "index-lookup: name=" + std::string{name};
            ev.captured_at = format_timestamp(end_time);
            result.evidence.push_back(ev);
        } else {
            auto end_time = std::chrono::system_clock::now();
            result.index_lookup_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            );
            
            // Name not in index - entity may still exist!
            result.status = core::SemanticStatus::kUnknown;
        }
        
        return result;
    }
    
    std::vector<IndexQueryResult> query_by_type(std::string_view type) override {
        std::vector<IndexQueryResult> results;
        
        if (!is_running_.load()) {
            return results;
        }
        
        // Find all entities with this type
        auto range = by_type_index_.equal_range(std::string{type});
        
        for (auto it = range.first; it != range.second; ++it) {
            IndexQueryResult result;
            result.status = core::SemanticStatus::kCompleted;
            result.found = true;
            result.entity_id = EntityId{it->second};
            result.source = IndexQueryResult::Source::kIndex;
            
            // Record evidence
            core::Evidence ev;
            ev.source = "inventory-index";
            ev.value = "index-lookup: type=" + std::string{type};
            ev.captured_at = format_timestamp(std::chrono::system_clock::now());
            result.evidence.push_back(ev);
            
            results.push_back(result);
        }
        
        return results;
    }
    
    IndexState get_index_state(IndexKind kind) const override {
        auto it = freshness_timestamps_.find(kind);
        if (it == freshness_timestamps_.end()) {
            return IndexState::kInitializing;
        }
        
        // Check staleness
        auto now = std::chrono::system_clock::now();
        auto elapsed = now - it->second;
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        
        if (elapsed_ms > stale_threshold_) {
            return IndexState::kStale;
        }
        
        // Check rebuild status
        if (is_rebuilding_.load()) {
            return IndexState::kRebuilding;
        }
        
        return IndexState::kReady;
    }
    
    IndexMetrics get_metrics() const override {
        IndexMetrics metrics;
        
        metrics.total_entries = by_id_index_.size();
        metrics.index_count = 5;  // kByName, kByType, kByLocation, kByTag, kByState
        
        auto now = std::chrono::system_clock::now();
        if (!rebuild_times_.empty()) {
            auto last_rebuild = rebuild_times_.back();
            metrics.last_build_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - last_rebuild
            );
        }
        
        return metrics;
    }
    
private:
    size_t build_index_for_kind(IndexKind kind, size_t max_entries) {
        // This is a placeholder implementation that builds a minimal index.
        // In a real implementation, this would:
        // 1. Query source truth (procfs, sysfs, systemd, etc.)
        // 2. Build the appropriate index map
        // 3. Update freshness timestamp
        
        size_t entries = 0;
        
        switch (kind) {
            case IndexKind::kByName:
                // Build by-name index (placeholder)
                break;
            case IndexKind::kByType:
                // Build by-type index (placeholder)
                break;
            case IndexKind::kByLocation:
                // Build by-location index (placeholder)
                break;
            case IndexKind::kByTag:
                // Build by-tag index (placeholder)
                break;
            case IndexKind::kByState:
                // Build by-state index (placeholder)
                break;
        }
        
        freshness_timestamps_[kind] = std::chrono::system_clock::now();
        
        return entries;
    }
    
    static std::string format_timestamp(std::chrono::system_clock::time_point tp) {
        auto time_t_val = std::chrono::system_clock::to_time_t(tp);
        std::tm tm_val;
        gmtime_r(&time_t_val, &tm_val);
        
        char buf[64];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02dT%02d:%02d:%02dZ",
                 tm_val.tm_year + 1900, tm_val.tm_mon + 1, tm_val.tm_mday,
                 tm_val.tm_hour, tm_val.tm_min, tm_val.tm_sec);
        
        return std::string{buf};
    }
    
private:
    std::chrono::milliseconds stale_threshold_{60000};  // Default: 60 seconds
    size_t max_entries_per_index_{100000};
    
    std::atomic<bool> is_running_{false};
    std::atomic<bool> is_rebuilding_{false};
    
    // Index structures (placeholder - would be populated from source truth)
    std::unordered_map<std::string, std::string> by_id_index_;      // id -> entity_data
    std::unordered_multimap<std::string, std::string> by_name_index_;  // name -> id
    std::unordered_multimap<std::string, std::string> by_type_index_;  // type -> id
    
    // Freshness tracking per index kind
    std::unordered_map<IndexKind, std::chrono::system_clock::time_point> freshness_timestamps_;
    
    // Rebuild timestamps for metrics
    std::vector<std::chrono::system_clock::time_point> rebuild_times_;
};

// ============================================================================
// make_inventory_indexer — Factory function
// ============================================================================
std::unique_ptr<InventoryIndexer> make_inventory_indexer() {
    return std::make_unique<InventoryIndexerImpl>();
}

}  // namespace rebuntu::interfaces