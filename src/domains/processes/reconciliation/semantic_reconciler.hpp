#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::processes::reconciliation {
inline common::DomainReconciler semantic_reconciler() { auto s=common::process_semantics(); return {std::move(s.profile),std::move(s.operations)}; }
}
