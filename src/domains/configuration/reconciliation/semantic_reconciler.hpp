#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::configuration::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::configuration_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
