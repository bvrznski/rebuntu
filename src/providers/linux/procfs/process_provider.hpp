#pragma once
#include "../../../core/types.hpp"
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::providers::linux::procfs {
struct ProcessSnapshot {
  int pid{-1}; int ppid{-1}; unsigned long long start_ticks{0};
  std::string comm; std::string state; std::vector<std::string> command;
};
class ProcessProvider {
public:
  virtual ~ProcessProvider() = default;
  virtual std::optional<ProcessSnapshot> observe(int pid) = 0;
  virtual bool execute(const core::NativeOperation& operation) = 0;
};
}
