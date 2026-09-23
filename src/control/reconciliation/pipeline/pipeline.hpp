#pragma once
#include "../../../core/types.hpp"
#include "../../../core/verification/verification_report.hpp"
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::control::reconciliation::pipeline {

struct Observation {
  core::Entity entity;
  bool authoritative{false};
};

struct PolicyDecision {
  bool allowed{true};
  std::vector<std::string> reasons;
};

struct Result {
  enum class Status { converged, planned, applied, blocked, failed } status{Status::failed};
  core::Plan plan;
  core::Verification verification;
  std::vector<std::string> trace;
};

class Observer {
public:
  virtual ~Observer() = default;
  virtual std::optional<Observation> observe(const std::string& entity_id) = 0;
};
class Planner {
public:
  virtual ~Planner() = default;
  virtual core::Plan synthesize(const core::DesiredState&, const core::Entity&) = 0;
};
class Policy {
public:
  virtual ~Policy() = default;
  virtual PolicyDecision authorize(const core::Plan&, const core::Entity&) = 0;
};
class Executor {
public:
  virtual ~Executor() = default;
  virtual bool execute(const core::NativeOperation&) = 0;
};
class Verifier {
public:
  virtual ~Verifier() = default;
  virtual core::Verification verify(const core::DesiredState&, const core::Entity&) = 0;
};

class Pipeline {
  Observer& observer_; Planner& planner_; Policy& policy_; Executor& executor_; Verifier& verifier_;
public:
  Pipeline(Observer& o, Planner& p, Policy& a, Executor& e, Verifier& v)
      : observer_(o), planner_(p), policy_(a), executor_(e), verifier_(v) {}
  Result reconcile(const core::DesiredState& desired, bool apply);
};

} // namespace rebuntu::control::reconciliation::pipeline
