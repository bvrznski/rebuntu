#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::identity::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::identity_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
