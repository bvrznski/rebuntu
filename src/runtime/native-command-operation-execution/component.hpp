#pragma once

#include <string_view>

namespace rebuntu::runtime::native_command_operation_execution {

// Structural integration point for native command operation execution.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class NativeCommandOperationExecutionComponent {
public:
    virtual ~NativeCommandOperationExecutionComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "native-command-operation-execution"; }
};

} // namespace rebuntu::runtime::native_command_operation_execution
