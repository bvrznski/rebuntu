#include <runtime/production.hpp>
#include <cassert>
#include <iostream>
using namespace rebuntu;
int main(){
  using namespace runtime::production;
  
  std::cout << "Phase 4.18 Startup, Init & Dependency Chains Tests\n";
  std::cout << "====================================================\n\n";
  
  // Test 1: Linear dependencies (a -> b -> c)
  {
    Initializer init; 
    RuntimeContext c; 
    c.runtime_id="test_linear";
    
    auto order = init.startup_order({
      {"a", {}, true, true},
      {"b", {"a"}, true, true},
      {"c", {"b"}, true, true}
    });
    
    assert(order.has_value() && "Linear dependencies should have a valid order");
    assert(order->size() == 3 && "Order should contain all 3 items");
    assert((*order)[0] == "a" && (*order)[1] == "b" && (*order)[2] == "c" &&
           "Order should be: a, b, c (dependency order)");
    
    std::cout << "[PASS] Linear dependencies test\n";
  }
  
  // Test 2: Multiple roots with one dependency
  {
    Initializer init;
    RuntimeContext c;
    c.runtime_id="test_multiroot";
    
    auto order = init.startup_order({
      {"a", {}, true, true},
      {"b", {}, true, true},
      {"c", {"a"}, true, true}
    });
    
    assert(order.has_value() && "Multiple roots should have a valid order");
    assert(order->size() == 3);
    
    // c must come after a
    auto a_pos = std::find(order->begin(), order->end(), "a") - order->begin();
    auto c_pos = std::find(order->begin(), order->end(), "c") - order->begin();
    assert(c_pos > a_pos && "c depends on a, so c should come after a");
    
    std::cout << "[PASS] Multiple roots with one dependency test\n";
  }
  
  // Test 3: Cycle detection
  {
    Initializer init;
    RuntimeContext c;
    c.runtime_id="test_cycle";
    
    auto order = init.startup_order({
      {"a", {"b"}, true, true},
      {"b", {"a"}, true, true}  // Creates cycle a -> b -> a
    });
    
    assert(!order.has_value() && "Cyclic dependencies should return nullopt");
    
    std::cout << "[PASS] Cycle detection test\n";
  }
  
  // Test 4: Unready dependency (required)
  {
    Initializer init;
    RuntimeContext c;
    c.runtime_id="test_unready";
    
    auto result = init.initialize(c, {
      {"a", {}, true, false},   // a is not ready
      {"b", {"a"}, true, true}  // b depends on a (not ready)
    });
    
    assert(result.outcome.status == core::SemanticStatus::kFailure &&
           "Unready required dependency should cause failure");
    
    std::cout << "[PASS] Unready required dependency test\n";
  }
  
  // Test 5: Self-dependency cycle
  {
    Initializer init;
    RuntimeContext c;
    c.runtime_id="test_selfcycle";
    
    auto order = init.startup_order({
      {"a", {"a"}, true, true}  // a depends on itself
    });
    
    assert(!order.has_value() && "Self-dependency should be detected as cycle");
    
    std::cout << "[PASS] Self-dependency cycle test\n";
  }
  
  // Test 6: Empty dependency list (no dependencies)
  {
    Initializer init;
    RuntimeContext c;
    c.runtime_id="test_empty";
    
    auto order = init.startup_order({});
    
    assert(order.has_value() && "Empty deps should return empty order");
    assert(order->empty() && "Order should be empty for no dependencies");
    
    std::cout << "[PASS] Empty dependency list test\n";
  }
  
  // Test 7: Complex graph with multiple branches
  {
    Initializer init;
    RuntimeContext c;
    c.runtime_id="test_complex";
    
    auto order = init.startup_order({
      {"a", {}, true, true},
      {"b", {}, true, true},
      {"c", {"a", "b"}, true, true},  // depends on both a and b
      {"d", {"c"}, true, true}        // depends on c
    });
    
    assert(order.has_value() && "Complex graph should have valid order");
    assert(order->size() == 4);
    
    // Verify ordering constraints
    auto get_pos = [&](const std::string& id) {
      return std::find(order->begin(), order->end(), id) - order->begin();
    };
    
    size_t a_pos = get_pos("a");
    size_t b_pos = get_pos("b");
    size_t c_pos = get_pos("c");
    size_t d_pos = get_pos("d");
    
    assert(c_pos > a_pos && "c depends on a");
    assert(c_pos > b_pos && "c depends on b");
    assert(d_pos > c_pos && "d depends on c");
    
    std::cout << "[PASS] Complex graph with multiple branches test\n";
  }
  
  std::cout << "\nAll Phase 4.18 dependency chain tests passed!\n";
  return 0;
}