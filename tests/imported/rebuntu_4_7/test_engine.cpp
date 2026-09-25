// Unit tests for rebuntu::runtime::engine (Phase 4.2)
// Minimal, dependency-free assertion harness.
#include <runtime/engine.hpp>

#include <iostream>
#include <chrono>
#include <memory>

namespace {
int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)
}  // namespace

int main() {
    using rebuntu::runtime::engine::EngineState;
    using rebuntu::runtime::engine::to_string;
    
    // Test engine state string conversions
    CHECK(to_string(EngineState::kCreated) == "created");
    CHECK(to_string(EngineState::kInitializing) == "initializing");
    CHECK(to_string(EngineState::kReady) == "ready");
    CHECK(to_string(EngineState::kStopping) == "stopping");
    CHECK(to_string(EngineState::kStopped) == "stopped");
    CHECK(to_string(EngineState::kFailed) == "failed");
    
    // Test Engine construction
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        CHECK(engine != nullptr);
        CHECK(engine->get_state() == EngineState::kCreated);
    }
    
    // Test Engine initialization
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        auto result = engine->initialize();
        CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess ||
              result.status == rebuntu::core::SemanticStatus::kCompleted);
        CHECK(engine->get_state() == EngineState::kReady || 
              engine->get_state() == EngineState::kInitializing);
    }
    
    // Test is_ready
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        CHECK(engine->is_ready() == false);
        
        engine->initialize();
        CHECK(engine->is_ready() == true);
    }
    
    // Test EngineBuilder
    {
        auto engine = rebuntu::runtime::engine::EngineBuilder()
            .with_max_concurrent(50)
            .set_dry_run(true)
            .build();
        
        CHECK(engine != nullptr);
        CHECK(engine->get_state() == EngineState::kCreated);
    }
    
    // Test shutdown
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        engine->initialize();
        CHECK(engine->get_state() == EngineState::kReady);
        
        auto result = engine->shutdown();
        CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
        CHECK(engine->get_state() == EngineState::kStopped);
    }
    
    // Test get_health
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        auto health = engine->get_health();
        CHECK(health.status == rebuntu::core::SemanticStatus::kFailure ||
              health.status == rebuntu::core::SemanticStatus::kUnknown);
        
        engine->initialize();
        health = engine->get_health();
        CHECK(health.status == rebuntu::core::SemanticStatus::kSuccess);
    }
    
    // Test execute_work request
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        engine->initialize();
        
        rebuntu::runtime::work::Task task;
        task.id.value = "test-task";
        task.title = "Test Task";
        task.description = "A test task for the engine";
        task.unit_id = "system.test";
        task.mode = rebuntu::runtime::work::ExecutionMode::kInline;
        
        rebuntu::runtime::work::Job job;
        job.id.value = "test-job-123";
        job.task_id = "test-task";
        job.created_at = std::chrono::system_clock::now();
        
        rebuntu::runtime::engine::ExecuteWorkRequest req;
        req.task = task;
        req.job = job;
        
        auto response = engine->execute_work(req);
        CHECK(response.status == rebuntu::core::SemanticStatus::kSuccess ||
              response.status == rebuntu::core::SemanticStatus::kCompleted);
    }
    
    // Test lifecycle commands
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        rebuntu::runtime::engine::LifecycleRequest req;
        req.command = rebuntu::runtime::engine::LifecycleCommand::kStart;
        
        auto response = engine->lifecycle(req);
        CHECK(response.status == rebuntu::core::SemanticStatus::kSuccess ||
              response.status == rebuntu::core::SemanticStatus::kCompleted);
    }
    
    // Test query_state
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        engine->initialize();
        
        rebuntu::runtime::engine::QueryStateRequest req;
        req.type = rebuntu::runtime::engine::QueryType::kEngineState;
        
        auto response = engine->query_state(req);
        CHECK(response.status == rebuntu::core::SemanticStatus::kSuccess ||
              response.status == rebuntu::core::SemanticStatus::kCompleted);
    }
    
    // Test workflow request
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        engine->initialize();
        
        rebuntu::runtime::workflow::WorkflowDefinition wf;
        wf.id = "test-workflow";
        
        rebuntu::runtime::engine::WorkflowRequest req;
        req.definition = wf;
        
        auto response = engine->workflow(req);
        CHECK(response.status == rebuntu::core::SemanticStatus::kSuccess ||
              response.status == rebuntu::core::SemanticStatus::kCompleted);
    }
    
    // Test cancel request
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        engine->initialize();
        
        rebuntu::runtime::engine::CancelRequest req;
        req.execution_id = "test-exec-123";
        
        auto response = engine->cancel(req);
        CHECK(response.status == rebuntu::core::SemanticStatus::kSuccess ||
              response.status == rebuntu::core::SemanticStatus::kCompleted);
    }
    
    // Test get_statistics
    {
        rebuntu::runtime::engine::EngineContext ctx;
        auto engine = std::make_unique<rebuntu::runtime::engine::Engine>(ctx);
        
        auto stats = engine->get_statistics();
        CHECK(stats.requests_received == 0);
        CHECK(stats.work_items_started == 0);
    }
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_engine: OK\n";
    return 0;
}