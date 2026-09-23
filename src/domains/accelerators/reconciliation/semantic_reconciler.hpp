#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::accelerators::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::accelerator_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
