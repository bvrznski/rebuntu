// rebuntu::shell::context tests (Phase 6.15)
//
// Tests for bounded contextual command resolution.

#include <system/shell/context.hpp>
#include <system/shell/types.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::shell;

void test_make_empty() {
    Context ctx = Context::make_empty();
    assert(ctx.empty());
}

void test_set_and_get() {
    Context& ctx = Context::instance();
    
    // Set a subject context
    ctx.set(ContextKind::kSubject, "current", "package");
    
    std::string value;
    bool found = ctx.get(ContextKind::kSubject, "current", value);
    assert(found);
    assert(value == "package");
}

void test_set_explicit() {
    Context& ctx = Context::instance();
    
    // Set with explicit marker
    ctx.set_explicit(ContextKind::kScope, "default", "system");
    
    std::string value;
    bool found = ctx.get(ContextKind::kScope, "default", value);
    assert(found);
    assert(value == "system");
}

void test_remove() {
    Context& ctx = Context::instance();
    
    // Add and remove
    ctx.set(ContextKind::kOutputMode, "preferred", "structured");
    assert(!ctx.empty());
    
    ctx.remove(ContextKind::kOutputMode, "preferred");
    
    std::string value;
    bool found = ctx.get(ContextKind::kOutputMode, "preferred", value);
    assert(!found);
}

void test_reset_kind() {
    Context& ctx = Context::instance();
    
    // Add some entries
    ctx.set(ContextKind::kSubject, "s1", "v1");
    ctx.set(ContextKind::kScope, "default", "system");
    assert(!ctx.empty());
    
    // Reset specific kind
    ctx.reset_kind(ContextKind::kSubject);
    
    std::string value;
    bool found = ctx.get(ContextKind::kSubject, "s1", value);
    assert(!found);  // kSubject entries removed
    
    found = ctx.get(ContextKind::kScope, "default", value);
    assert(found);   // kScope still present
}

void test_reset_all() {
    Context& ctx = Context::instance();
    
    ctx.set(ContextKind::kSubject, "current", "package");
    ctx.set(ContextKind::kScope, "default", "system");
    
    ctx.reset_all();
    
    assert(ctx.empty());
}

void test_to_string() {
    assert(to_string(ContextKind::kSubject) == "subject");
    assert(to_string(ContextKind::kScope) == "scope");
    assert(to_string(ContextKind::kOutputMode) == "output_mode");
    assert(to_string(ContextKind::kQualifier) == "qualifier");
    assert(to_string(ContextKind::kTargetCache) == "target_cache");
}

void test_inspect_context() {
    Context& ctx = Context::instance();
    
    // Clear context first
    ctx.reset_all();
    
    // Add some values
    ctx.set(ContextKind::kSubject, "current", "service");
    ctx.set(ContextKind::kScope, "default", "system");
    
    auto inspection = inspect_context();
    
    assert(inspection.has_context);
    assert(!inspection.active_kinds.empty());
}

void test_scope_resolution() {
    Context& ctx = Context::instance();
    
    // Test with explicit scope (using int values to match interface)
    int result1 = ContextManager::get_scope_with_resolution(1, true);  // SYSTEM scope as int
    assert(result1 == 1);
    
    // Test without explicit scope (should fall back to context)
    int result2 = ContextManager::get_scope_with_resolution(0, false);
    // Should return 0 (USER) when no context is set
    assert(result2 == 0);
}

int main() {
    std::cout << "Testing shell context module (Phase 6.15)\n";
    
    test_make_empty();
    std::cout << "  make_empty: PASS\n";
    
    test_set_and_get();
    std::cout << "  set/get: PASS\n";
    
    test_set_explicit();
    std::cout << "  set_explicit: PASS\n";
    
    test_remove();
    std::cout << "  remove: PASS\n";
    
    test_reset_kind();
    std::cout << "  reset_kind: PASS\n";
    
    test_reset_all();
    std::cout << "  reset_all: PASS\n";
    
    test_to_string();
    std::cout << "  to_string: PASS\n";
    
    test_inspect_context();
    std::cout << "  inspect_context: PASS\n";
    
    test_scope_resolution();
    std::cout << "  scope_resolution: PASS\n";
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}