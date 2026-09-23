#pragma once

#include <string_view>

namespace rebuntu::knowledge::system_knowledge_graph {

// Structural integration point for system knowledge graph.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemKnowledgeGraphComponent {
public:
    virtual ~SystemKnowledgeGraphComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-knowledge-graph"; }
};

} // namespace rebuntu::knowledge::system_knowledge_graph
