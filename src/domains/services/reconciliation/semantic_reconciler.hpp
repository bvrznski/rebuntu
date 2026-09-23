#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::services::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::service_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
