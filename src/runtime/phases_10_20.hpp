#pragma once
#include <chrono>
#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace rebuntu::platform {
using Fields = std::map<std::string,std::string>;
struct Evidence { std::string kind, source, detail; bool verified{false}; };
struct Decision { bool allowed{false}; std::string reason; std::vector<Evidence> evidence; };
enum class Status { pending, running, succeeded, failed, cancelled, degraded, quarantined };

// Phase 10 — production workflow graph/runtime semantics.
namespace workflow {
struct Retry { unsigned max_attempts{1}; std::chrono::milliseconds backoff{0}; };
struct Step { std::string id, capability; std::vector<std::string> depends_on; Fields inputs; Retry retry; bool reversible{false}; std::string compensation; };
struct Definition { std::string id, version; std::vector<Step> steps; };
struct StepResult { std::string id; Status status{Status::pending}; Fields outputs; std::vector<Evidence> evidence; unsigned attempts{0}; };
struct Checkpoint { std::string workflow_id, version; std::set<std::string> completed; Fields data; };
struct Report { Status status{Status::pending}; std::vector<StepResult> steps; std::vector<std::string> audit; bool verified{false}; };
class Engine {
public:
 using Capability = std::function<StepResult(const Step&, const Fields&)>;
 void register_capability(std::string name, Capability fn);
 std::vector<std::string> validate(const Definition&) const;
 std::vector<std::string> plan(const Definition&) const;
 Report run(const Definition&, Fields input={}, const Checkpoint* resume=nullptr, std::function<bool(const Step&,const Fields&)> gate={});
private: std::unordered_map<std::string,Capability> capabilities_;
};
}

// Phase 11 — layered, validated configuration and composable profiles.
namespace config {
enum class Layer { defaults=0, host=10, user=20, workload=30, environment=40, runtime=50 };
struct Entry { std::string key, value, source; Layer layer{Layer::defaults}; };
struct Rule { std::string key; bool required{false}; std::optional<std::string> prefix; };
struct Profile { std::string name; Layer layer{Layer::runtime}; Fields values; std::vector<std::string> includes; };
struct Diff { std::string key; std::optional<std::string> before, after; };
class Store {
public:
 void set(Entry); void define(Profile); std::optional<std::string> get(const std::string&) const;
 Fields effective() const; Fields compose(const std::vector<std::string>&) const;
 std::vector<Diff> diff(const Fields&) const; std::vector<std::string> validate(const std::vector<Rule>&) const;
 Decision apply(const Fields&, std::function<bool(const std::string&,const std::string&)> applier) const;
private: std::map<std::string,Entry> entries_; std::map<std::string,Profile> profiles_;
};
}

// Phase 12 — stability, classification, recovery and safety policy.
namespace stability {
enum class Failure { deviation, degradation, stall, crash, boot, filesystem, storage, service, unknown };
enum class Recovery { retry, restart, repair, restore, rollback, compensate, degrade, none };
struct Baseline { Fields metrics; };
struct Incident { Failure failure{Failure::unknown}; std::string subject; std::vector<Evidence> evidence; unsigned severity{0}; };
struct Plan { Recovery action{Recovery::none}; std::string subject; bool destructive{false}; std::vector<std::string> steps; };
class Manager {
public:
 void baseline(Baseline b); std::vector<std::string> deviations(const Fields&) const;
 Incident classify(std::string subject, const Fields&, std::vector<Evidence> = {}) const;
 Plan recovery(const Incident&) const; Decision authorize(const Plan&, bool maintenance_mode) const;
 bool verify(const Baseline&, const Fields&) const;
private: Baseline baseline_;
};
}

// Phase 13 — identity/capability/scope/policy/secrets/audit/quarantine.
namespace security {
struct Principal { std::string id; std::set<std::string> roles, capabilities, scopes; bool authenticated{false}; };
struct Request { std::string operation, scope; std::set<std::string> capabilities; bool destructive{false}; };
struct AuditRecord { std::uint64_t sequence{}; std::string principal, operation, outcome; Fields context; };
class Guard {
public:
 void policy(std::string operation, std::set<std::string> roles);
 Decision authorize(const Principal&, const Request&) const;
 std::string seal_secret(std::string_view) const; std::optional<std::string> open_secret(std::string_view) const;
 void record(const Principal&, const Request&, const Decision&); const std::vector<AuditRecord>& audit() const { return audit_; }
 void quarantine(std::string subject); bool quarantined(const std::string&) const;
private: std::map<std::string,std::set<std::string>> policies_; std::vector<AuditRecord> audit_; std::set<std::string> quarantine_; std::uint64_t seq_{0};
};
}

// Phase 14 — discovery, profiles, arbitration and performance verification.
namespace resources {
struct Snapshot { unsigned cpu_count{}; std::uint64_t memory_total_kib{}, memory_available_kib{}; double load1{}; std::vector<std::string> gpus; Fields thermal, power; };
struct Profile { std::string name; unsigned cpu_quota_percent{100}; int nice{0}; std::optional<std::string> gpu; std::uint64_t memory_limit_kib{0}; };
struct Claim { std::string owner; unsigned cpu_percent{}; std::uint64_t memory_kib{}; std::optional<std::string> gpu; int priority{}; };
class Manager {
public:
 Snapshot discover() const; Decision validate(const Profile&, const Snapshot&) const;
 Decision claim(Claim); void release(const std::string&); std::vector<Claim> claims() const;
 Fields benchmark(std::chrono::milliseconds budget=std::chrono::milliseconds{20}) const;
private: std::map<std::string,Claim> claims_;
};
}

// Phase 15 — Linux environment/device/session coordination.
namespace environment {
enum class DeviceKind { display, audio, input, storage, network, bluetooth, gpu, unknown };
struct Device { std::string id, path; DeviceKind kind{DeviceKind::unknown}; bool present{true}; Fields properties; };
struct Layout { Fields display_positions; std::string primary; };
class Coordinator {
public:
 std::vector<Device> discover() const; std::vector<Device> diff(const std::vector<Device>& before,const std::vector<Device>& after) const;
 Decision validate_layout(const Layout&, const std::vector<Device>&) const;
 Fields session() const; std::vector<std::string> mounts() const; std::vector<std::string> interfaces() const;
};
}

// Phase 16 — maintenance planning, drift/integrity and safe cleanup.
namespace maintenance {
struct Item { std::string path, category; std::uint64_t bytes{}; bool safe_to_remove{false}; };
struct Plan { std::vector<Item> items; std::uint64_t reclaimable{}; bool requires_confirmation{false}; };
class Manager {
public:
 Fields package_state() const; Fields filesystem_state(const std::string& path="/") const;
 std::vector<std::string> drift(const Fields& desired,const Fields& observed) const;
 std::string digest_file(const std::string&) const; bool verify_file(const std::string&,const std::string&) const;
 Plan cleanup_plan(const std::vector<Item>&) const; Decision execute_cleanup(const Plan&, bool confirmed) const;
};
}

// Phase 17 — bounded semantic administration; never directly executes text.
namespace semantic {
struct Intent { std::string verb, object; Fields arguments; double confidence{}; bool ambiguous{false}; };
struct IR { std::string operation; Fields parameters; std::vector<std::string> unresolved; };
class Interpreter {
public:
 Intent parse(const std::string&) const; IR lower(const Intent&) const;
 std::vector<std::string> summarize(const std::vector<std::string>& logs, std::size_t limit=8) const;
 Decision safety(const IR&, const std::set<std::string>& registered_operations) const;
 IR deterministic_fallback(const std::string&) const;
};
}

// Phase 18 — capability registry, discovery, gaps, sandbox verification/versioning.
namespace capability {
struct Descriptor { std::string name, version, provider; std::set<std::string> tags; bool verified{false}, safe{false}; };
struct Gap { std::string requested; std::vector<std::string> missing; };
class Registry {
public:
 bool add(Descriptor); std::optional<Descriptor> get(const std::string&) const;
 std::vector<Descriptor> search(const std::set<std::string>& tags) const; Gap gap(const std::set<std::string>& required) const;
 Decision accept(const Descriptor&, const std::vector<Evidence>&) const; bool supersede(const std::string&, Descriptor);
 std::vector<std::string> providers() const;
private: std::map<std::string,Descriptor> items_;
};
}

// Phase 19 — desired/observed state reconciliation and bounded convergence.
namespace reconcile {
struct Delta { std::string key; std::optional<std::string> desired, observed; };
struct Plan { std::vector<Delta> deltas; unsigned max_iterations{3}; };
struct Result { bool converged{false}; unsigned iterations{}; std::vector<Delta> remaining; std::vector<Evidence> evidence; };
class Reconciler {
public:
 std::vector<Delta> compare(const Fields&,const Fields&) const; Plan plan(const Fields&,const Fields&,unsigned max_iterations=3) const;
 Result converge(const Fields& desired, Fields observed, std::function<bool(const Delta&)> apply) const;
};
}

// Phase 20 — whole-system integration facade and closure audit.
struct IntegrationReport { bool healthy{false}; std::map<std::string,bool> domains; std::vector<std::string> issues; std::vector<Evidence> evidence; };
class System {
public:
 workflow::Engine workflow; config::Store configuration; stability::Manager stability; security::Guard security;
 resources::Manager resources; environment::Coordinator environment; maintenance::Manager maintenance;
 semantic::Interpreter semantic; capability::Registry capabilities; reconcile::Reconciler reconciler;
 IntegrationReport audit() const;
};
}
