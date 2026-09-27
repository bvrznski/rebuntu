// rebuntu::shell::verbs::list — List Command Implementation

#include "list.hpp"
#include "../parser.hpp"

namespace rebuntu::shell::verbs {

CommandResult list_command(const CommandIntent& intent) {
    // Validate intent
    if (intent.kind != IntentKind::kVerb || intent.verb != "list") {
        return CommandResult::failure("E_INVALID_INPUT", "not a list command");
    }
    
    CommandResult result;
    result.status = core::SemanticStatus::kSuccess;
    
    // Add evidence for what we're listing
    core::Evidence e;
    e.source = "shell";
    e.value = "list:" + intent.verb;
    result.evidence.push_back(std::move(e));
    
    return result;
}

}  // namespace rebuntu::shell::verbs