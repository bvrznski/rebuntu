#pragma once
#include "../model.hpp"
namespace rebuntu::domains::common::health {
enum class Status { healthy, degraded, failed, unknown };
inline Status aggregate(const Health& h){ if(h.signals.empty()) return Status::unknown; bool degraded=false; for(const auto& s:h.signals){if(s.status=="failed") return Status::failed; if(s.status=="degraded") degraded=true;} return degraded?Status::degraded:Status::healthy; }
}
