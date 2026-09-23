#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::storage::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::storage_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
