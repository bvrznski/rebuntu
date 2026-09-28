// rebuntu::command::dependencies — Typed Dependency-Aware Execution (Phase 6.45)
//
// This module provides explicit dependency representation for operations:
//
//   * Dependency: Explicit relationship between operations where one waits for another
//   * DependencyGraph: Collection of dependencies with topological ordering
//   * DependencyResolver: Determines execution order from dependency graph
//   * DependencyAwareIntent: Intent that includes explicit dependencies
//
// Design Philosophy:
//   * Dependencies are EXPLICIT, not implicit via shell `&&` chains
//   * Each operation can depend on prior operations completing successfully
//   * Execution order is determined by dependency analysis, not manual sequencing
//   * Circular dependencies are detected and reported as errors
//
// Key Principles:
//   * Dependency represents "this must complete before that starts"
//   * Dependencies drive execution scheduling, not manual ordering
//   * Each step can wait for specific prior results (not just previous step)
//   * Failed dependencies can trigger early termination or best-effort continuation

#pragma once

#include "model.hpp"
#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

namespace rebuntu::command {

// ============================================================================
// Dependency — Explicit relationship between operations
//
// A dependency declares that one operation must complete before another starts.
// This replaces implicit shell chaining with explicit semantic relationships.
// ============================================================================

enum class DependencyType {
    kSuccess,        // Wait for successful completion
    kCompletion,     // Wait for completion (success or failure)
    kResultReady,    // Wait for result to be available (not just completion)
};

inline std::string to_string(DependencyType t) {
    switch (t) {
        case DependencyType::kSuccess:     return "success";
        case DependencyType::kCompletion:  return "completion";
        case DependencyType::kResultReady: return "result_ready";
    }
    return "unknown";
}

struct Dependency {
    std::string target_id;       // ID of the operation this depends on
    DependencyType type;         // What condition must be met
    bool optional{false};        // If true, continue even if dependency fails
    
    static Dependency success(const std::string& target) {
        return Dependency{target, DependencyType::kSuccess, false};
    }
    
    static Dependency completion(const std::string& target) {
        return Dependency{target, DependencyType::kCompletion, false};
    }
    
    static Dependency optional_success(const std::string& target) {
        return Dependency{target, DependencyType::kSuccess, true};
    }
};

// ============================================================================
// DependencyGraph — Collection of operations with dependency relationships
//
// Represents a DAG of operations where edges are dependencies.
// Supports topological sorting for execution order determination.
// ============================================================================

struct DependencyNode {
    std::string id;              // Unique identifier for this node
    CommandIntent intent;        // The operation to execute
    std::vector<Dependency> deps;// Dependencies on other nodes
    bool optional{false};        // If true, failure doesn't block successors
    
    static DependencyNode make(std::string id, CommandIntent intent) {
        return DependencyNode{id, std::move(intent), {}, false};
    }
};

class DependencyGraph {
public:
    // Add a node with its dependencies
    void add_node(DependencyNode node);
    
    // Find the execution order (topological sort)
    // Returns empty vector if there's a cycle
    std::vector<std::string> topological_sort() const;
    
    // Get all nodes in the graph
    const std::unordered_map<std::string, DependencyNode>& nodes() const { return nodes_; }
    
    // Check for circular dependencies
    bool has_cycle() const;
    
    // Validate that all dependencies reference existing nodes
    std::vector<std::string> validate_dependencies() const;

private:
    std::unordered_map<std::string, DependencyNode> nodes_;
};

// ============================================================================
// DependencyResolver — Determines execution order from dependency graph
//
// Performs topological sort and identifies which operations can run in parallel.
// ============================================================================

struct ExecutionLevel {
    std::vector<std::string> node_ids;  // Nodes that can execute together
    bool is_parallel{true};             // True if all nodes are independent
};

class DependencyResolver {
public:
    // Analyze the graph and return execution levels
    // Each level contains nodes that can run in parallel
    std::vector<ExecutionLevel> resolve_execution_levels(
        const DependencyGraph& graph) const;
    
    // Get a single linear order (topological sort)
    std::vector<std::string> resolve_linear_order(
        const DependencyGraph& graph) const;
};

// ============================================================================
// DependencyAwareIntent — Intent that includes explicit dependencies
//
// Wraps a command intent with its dependency requirements.
// ============================================================================

struct DependencyAwareIntent {
    std::string id;                      // Unique ID for this intent
    CommandIntent base_intent;           // The underlying command intent
    std::vector<Dependency> dependencies;// Explicit dependencies on other intents
    
    // Factory method to create from an intent with dependencies
    static DependencyAwareIntent make(std::string id, 
                                       CommandIntent intent,
                                       std::vector<Dependency> deps = {}) {
        return DependencyAwareIntent{id, std::move(intent), std::move(deps)};
    }
};

// ============================================================================
// DependencyAwareSequence — Sequence of operations with dependency tracking
//
// Represents a composition where operations have explicit dependencies
// rather than just positional ordering.
// ============================================================================

struct DependencyAwareSequence {
    std::string id;                          // Unique sequence ID
    std::vector<DependencyAwareIntent> intents;
    std::optional<std::string> source_context;
    
    // Build the dependency graph from this sequence
    DependencyGraph build_graph() const;
    
    // Get execution order (topological sort of dependencies)
    std::vector<std::string> get_execution_order() const;
};

// ============================================================================
// Error codes for dependency operations
// ============================================================================

namespace error {
    constexpr const char kDependencyCycle[] = "E_DEPENDENCY_CYCLE";         // Circular dependency detected
    constexpr const char kMissingDependency[] = "E_MISSING_DEPENDENCY";     // Dependency references non-existent node
    constexpr const char kUnresolvableOrder[] = "E_UNRESOLVABLE_ORDER";     // Cannot determine execution order
}

// ============================================================================
// Inline implementations
// ============================================================================

inline void DependencyGraph::add_node(DependencyNode node) {
    nodes_[node.id] = std::move(node);
}

inline bool DependencyGraph::has_cycle() const {
    // Use DFS with three states: unvisited, visiting, visited
    std::unordered_map<std::string, int> state;  // 0=unvisited, 1=visiting, 2=visited
    
    auto dfs = [&](const std::string& node_id, auto&& self) -> bool {
        if (state[node_id] == 2) return false;  // Already visited, no cycle
        if (state[node_id] == 1) return true;   // Currently visiting, cycle found
        
        state[node_id] = 1;  // Mark as visiting
        
        auto it = nodes_.find(node_id);
        if (it != nodes_.end()) {
            for (const auto& dep : it->second.deps) {
                auto target_it = nodes_.find(dep.target_id);
                if (target_it != nodes_.end()) {
                    if (self(dep.target_id, self)) return true;
                }
            }
        }
        
        state[node_id] = 2;  // Mark as visited
        return false;
    };
    
    for (const auto& [id, node] : nodes_) {
        if (state[id] == 0) {
            if (dfs(id, dfs)) return true;
        }
    }
    
    return false;
}

inline std::vector<std::string> DependencyGraph::validate_dependencies() const {
    std::vector<std::string> errors;
    
    for (const auto& [id, node] : nodes_) {
        for (const auto& dep : node.deps) {
            if (nodes_.find(dep.target_id) == nodes_.end()) {
                errors.push_back("Node '" + id + "' depends on missing node '" + dep.target_id + "'");
            }
        }
    }
    
    return errors;
}

inline std::vector<std::string> DependencyGraph::topological_sort() const {
    // Kahn's algorithm for topological sort
    std::unordered_map<std::string, int> in_degree;
    std::vector<std::string> result;
    
    // Actually, dependencies mean: dependency must complete BEFORE this node
    // So edge is: dependency -> this_node
    // In-degree = number of dependencies
    
    for (const auto& [id, node] : nodes_) {
        int degree = 0;
        for (const auto& dep : node.deps) {
            if (nodes_.find(dep.target_id) != nodes_.end()) {
                degree++;
            }
        }
        in_degree[id] = degree;
    }
    
    // Start with nodes that have no dependencies
    std::vector<std::string> queue;
    for (const auto& [id, degree] : in_degree) {
        if (degree == 0) {
            queue.push_back(id);
        }
    }
    
    while (!queue.empty()) {
        std::string current = queue.back();
        queue.pop_back();
        result.push_back(current);
        
        // Find nodes that depend on this one
        for (const auto& [id, node] : nodes_) {
            bool depends_on_current = false;
            for (const auto& dep : node.deps) {
                if (dep.target_id == current && nodes_.find(dep.target_id) != nodes_.end()) {
                    depends_on_current = true;
                    break;
                }
            }
            
            if (depends_on_current) {
                in_degree[id]--;
                if (in_degree[id] == 0) {
                    queue.push_back(id);
                }
            }
        }
    }
    
    // If we didn't process all nodes, there's a cycle
    if (result.size() != nodes_.size()) {
        return {};  // Cycle detected
    }
    
    return result;
}

inline DependencyGraph DependencyAwareSequence::build_graph() const {
    DependencyGraph graph;
    
    for (const auto& intent : intents) {
        graph.add_node(DependencyNode{
            .id = intent.id,
            .intent = intent.base_intent,
            .deps = intent.dependencies
        });
    }
    
    return graph;
}

inline std::vector<std::string> DependencyAwareSequence::get_execution_order() const {
    auto graph = build_graph();
    return graph.topological_sort();
}

inline std::vector<ExecutionLevel> DependencyResolver::resolve_execution_levels(
    const DependencyGraph& graph) const {
    std::vector<ExecutionLevel> levels;
    
    if (graph.nodes().empty()) {
        return levels;
    }
    
    // Track which nodes are scheduled
    std::unordered_map<std::string, bool> scheduled;
    size_t total_nodes = graph.nodes().size();
    size_t processed = 0;
    
    // Safety limit to prevent infinite loops
    int max_iterations = static_cast<int>(total_nodes) + 1;
    int iteration = 0;
    
    while (processed < total_nodes && iteration < max_iterations) {
        ++iteration;
        
        ExecutionLevel level;
        
        // Find all nodes whose dependencies are satisfied in this round
        for (const auto& [id, node] : graph.nodes()) {
            if (scheduled.count(id)) continue;  // Already scheduled
            
            // Check if all dependencies are satisfied
            bool all_deps_satisfied = true;
            for (const auto& dep : node.deps) {
                auto it = scheduled.find(dep.target_id);
                if (it == scheduled.end() || !it->second) {
                    all_deps_satisfied = false;
                    break;
                }
            }
            
            if (all_deps_satisfied) {
                level.node_ids.push_back(id);
            }
        }
        
        // If no nodes could be scheduled, we have a cycle or missing dependency
        if (level.node_ids.empty()) {
            // Add remaining unscheduled nodes to catch cycles
            for (const auto& [id, node] : graph.nodes()) {
                if (!scheduled.count(id)) {
                    level.node_ids.push_back(id);
                }
            }
            
            // If we still can't add any nodes, break out
            if (level.node_ids.empty()) {
                break;
            }
        }
        
        level.is_parallel = level.node_ids.size() > 1;
        levels.push_back(std::move(level));
        
        // Mark all nodes in this level as scheduled
        for (const auto& id : level.node_ids) {
            if (!scheduled.count(id)) {
                scheduled[id] = true;
                processed++;
            }
        }
    }
    
    return levels;
}

inline std::vector<std::string> DependencyResolver::resolve_linear_order(
    const DependencyGraph& graph) const {
    return graph.topological_sort();
}

}  // namespace rebuntu::command