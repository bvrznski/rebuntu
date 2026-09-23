#pragma once
#include "../../core/types.hpp"
#include <set>
namespace rebuntu::security::policy {
class OperationPolicy { std::set<std::string> allowed_; public: explicit OperationPolicy(std::set<std::string> a):allowed_(std::move(a)){} bool permits(const core::NativeOperation& op) const { return !op.mutating || allowed_.contains(op.provider+":"+op.verb); } };
}
