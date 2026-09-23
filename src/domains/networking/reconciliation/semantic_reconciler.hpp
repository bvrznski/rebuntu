#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::networking::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::networking_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
