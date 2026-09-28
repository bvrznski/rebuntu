// rebuntu - Phase 6.45 Dependency-Aware Execution Unit Tests
//
// Tests for the dependency-aware execution module.
// Verifies explicit dependency representation, graph building,
// topological sorting, and circular dependency detection.

#include <system/command/dependencies.hpp>
#include <iostream>
#include <cassert>

using namespace rebuntu::command;

// Test Dependency type conversion
void test_dependency_type_to_string() {
    std::cout << "[TEST] DependencyType to_string...";
    
    assert(to_string(DependencyType::kSuccess) == "success");
    assert(to_string(DependencyType::kCompletion) == "completion");
    assert(to_string(DependencyType::kResultReady) == "result_ready");
    
    std::cout << " [PASS]\n";
}

// Test Dependency construction
void test_dependency_construction() {
    std::cout << "[TEST] Dependency construction...";
    
    auto dep = Dependency::success("target-1");
    assert(dep.target_id == "target-1");
    assert(dep.type == DependencyType::kSuccess);
    assert(!dep.optional);
    
    auto dep2 = Dependency::completion("target-2");
    assert(dep2.target_id == "target-2");
    assert(dep2.type == DependencyType::kCompletion);
    
    auto dep3 = Dependency::optional_success("target-3");
    assert(dep3.target_id == "target-3");
    assert(dep3.optional);
    
    std::cout << " [PASS]\n";
}

// Test DependencyNode construction
void test_dependency_node_construction() {
    std::cout << "[TEST] DependencyNode construction...";
    
    CommandIntent intent;
    intent.id = "test-intent";
    intent.verb = "status";
    
    auto node = DependencyNode::make("node-1", intent);
    assert(node.id == "node-1");
    assert(node.intent.id == "test-intent");
    assert(node.deps.empty());
    assert(!node.optional);
    
    std::cout << " [PASS]\n";
}

// Test DependencyGraph basic operations
void test_dependency_graph_basic() {
    std::cout << "[TEST] DependencyGraph basic operations...";
    
    DependencyGraph graph;
    
    CommandIntent intent1, intent2, intent3;
    intent1.id = "step-1";
    intent2.id = "step-2";
    intent3.id = "step-3";
    
    // Add nodes without dependencies
    graph.add_node(DependencyNode::make("node-1", intent1));
    graph.add_node(DependencyNode::make("node-2", intent2));
    
    assert(graph.nodes().size() == 2);
    assert(!graph.has_cycle());
    
    std::cout << " [PASS]\n";
}

// Test topological sort with simple dependencies
void test_topological_sort_simple() {
    std::cout << "[TEST] Topological sort with simple dependencies...";
    
    DependencyGraph graph;
    
    CommandIntent intent1, intent2, intent3;
    intent1.id = "step-1";
    intent2.id = "step-2";
    intent3.id = "step-3";
    
    // step-1 has no dependencies
    graph.add_node(DependencyNode::make("node-1", intent1));
    
    // step-2 depends on step-1
    graph.add_node(DependencyNode{
        .id = "node-2",
        .intent = intent2,
        .deps = {Dependency::success("node-1")}
    });
    
    // step-3 depends on step-2
    graph.add_node(DependencyNode{
        .id = "node-3",
        .intent = intent3,
        .deps = {Dependency::success("node-2")}
    });
    
    auto order = graph.topological_sort();
    
    assert(order.size() == 3);
    // node-1 should come before node-2, which comes before node-3
    size_t pos_1 = 0, pos_2 = 0, pos_3 = 0;
    for (size_t i = 0; i < order.size(); ++i) {
        if (order[i] == "node-1") pos_1 = i;
        else if (order[i] == "node-2") pos_2 = i;
        else if (order[i] == "node-3") pos_3 = i;
    }
    
    assert(pos_1 < pos_2 && pos_2 < pos_3);
    
    std::cout << " [PASS]\n";
}

// Test circular dependency detection
void test_circular_dependency_detection() {
    std::cout << "[TEST] Circular dependency detection...";
    
    DependencyGraph graph;
    
    CommandIntent intent1, intent2;
    intent1.id = "step-1";
    intent2.id = "step-2";
    
    // node-1 depends on node-2
    graph.add_node(DependencyNode{
        .id = "node-1",
        .intent = intent1,
        .deps = {Dependency::success("node-2")}
    });
    
    // node-2 depends on node-1 (cycle!)
    graph.add_node(DependencyNode{
        .id = "node-2",
        .intent = intent2,
        .deps = {Dependency::success("node-1")}
    });
    
    assert(graph.has_cycle());
    
    auto order = graph.topological_sort();
    assert(order.empty());  // Empty on cycle
    
    std::cout << " [PASS]\n";
}

// Test missing dependency validation
void test_missing_dependency_validation() {
    std::cout << "[TEST] Missing dependency validation...";
    
    DependencyGraph graph;
    
    CommandIntent intent1, intent2;
    intent1.id = "step-1";
    intent2.id = "step-2";
    
    // node-2 depends on non-existent node
    graph.add_node(DependencyNode::make("node-1", intent1));
    graph.add_node(DependencyNode{
        .id = "node-2",
        .intent = intent2,
        .deps = {Dependency::success("non-existent")}
    });
    
    auto errors = graph.validate_dependencies();
    assert(!errors.empty());
    assert(errors.size() == 1);
    assert(errors[0].find("non-existent") != std::string::npos);
    
    std::cout << " [PASS]\n";
}

// Test DependencyAwareIntent
void test_dependency_aware_intent() {
    std::cout << "[TEST] DependencyAwareIntent...";
    
    CommandIntent base;
    base.id = "base-intent";
    base.verb = "execute";
    
    auto aware = DependencyAwareIntent::make(
        "dependent-1",
        base,
        {Dependency::success("dependency-id")}
    );
    
    assert(aware.id == "dependent-1");
    assert(aware.base_intent.id == "base-intent");
    assert(aware.dependencies.size() == 1);
    assert(aware.dependencies[0].target_id == "dependency-id");
    
    std::cout << " [PASS]\n";
}

// Test DependencyAwareSequence
void test_dependency_aware_sequence() {
    std::cout << "[TEST] DependencyAwareSequence...";
    
    CommandIntent intent1, intent2, intent3;
    intent1.id = "step-1";
    intent2.id = "step-2";
    intent3.id = "step-3";
    
    auto seq = DependencyAwareSequence{};
    seq.id = "test-seq";
    
    // step-2 depends on step-1
    seq.intents.push_back(DependencyAwareIntent::make(
        "node-1", intent1, {}
    ));
    seq.intents.push_back(DependencyAwareIntent::make(
        "node-2", intent2,
        {Dependency::success("node-1")}
    ));
    
    auto graph = seq.build_graph();
    assert(graph.nodes().size() == 2);
    
    auto order = seq.get_execution_order();
    assert(order.size() == 2);
    assert(order[0] == "node-1");
    assert(order[1] == "node-2");
    
    std::cout << " [PASS]\n";
}

// Test parallel execution levels
void test_parallel_execution_levels() {
    std::cout << "[TEST] Parallel execution levels...";
    
    DependencyGraph graph;
    
    CommandIntent intent1, intent2, intent3, intent4;
    intent1.id = "a";
    intent2.id = "b";
    intent3.id = "c";
    intent4.id = "d";
    
    // a and b have no dependencies (can run in parallel)
    graph.add_node(DependencyNode::make("a", intent1));
    graph.add_node(DependencyNode::make("b", intent2));
    
    // c depends on a
    graph.add_node(DependencyNode{
        .id = "c",
        .intent = intent3,
        .deps = {Dependency::success("a")}
    });
    
    // d depends on b (but not on c - independent)
    graph.add_node(DependencyNode{
        .id = "d",
        .intent = intent4,
        .deps = {Dependency::success("b")}
    });
    
    DependencyResolver resolver;
    auto levels = resolver.resolve_execution_levels(graph);
    
    assert(levels.size() >= 2);  // At least: (a,b), then (c,d) or (c),(d)
    
    // First level should have independent nodes
    assert(levels[0].node_ids.size() == 2);
    assert(std::find(levels[0].node_ids.begin(), levels[0].node_ids.end(), "a") != 
           levels[0].node_ids.end());
    assert(std::find(levels[0].node_ids.begin(), levels[0].node_ids.end(), "b") != 
           levels[0].node_ids.end());
    
    std::cout << " [PASS]\n";
}

// Test linear order resolution
void test_linear_order_resolution() {
    std::cout << "[TEST] Linear order resolution...";
    
    DependencyGraph graph;
    
    CommandIntent intent1, intent2, intent3;
    intent1.id = "step-1";
    intent2.id = "step-2";
    intent3.id = "step-3";
    
    graph.add_node(DependencyNode::make("node-1", intent1));
    
    graph.add_node(DependencyNode{
        .id = "node-2",
        .intent = intent2,
        .deps = {Dependency::success("node-1")}
    });
    
    graph.add_node(DependencyNode{
        .id = "node-3",
        .intent = intent3,
        .deps = {Dependency::success("node-2")}
    });
    
    DependencyResolver resolver;
    auto order = resolver.resolve_linear_order(graph);
    
    assert(order.size() == 3);
    assert(order[0] == "node-1");
    assert(order[1] == "node-2");
    assert(order[2] == "node-3");
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "=== Phase 6.45 Dependency-Aware Execution Unit Tests ===\n\n";
    
    test_dependency_type_to_string();
    test_dependency_construction();
    test_dependency_node_construction();
    test_dependency_graph_basic();
    test_topological_sort_simple();
    test_circular_dependency_detection();
    test_missing_dependency_validation();
    test_dependency_aware_intent();
    test_dependency_aware_sequence();
    test_parallel_execution_levels();
    test_linear_order_resolution();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}