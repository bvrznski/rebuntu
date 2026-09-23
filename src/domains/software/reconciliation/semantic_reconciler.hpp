#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::software::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::software_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
