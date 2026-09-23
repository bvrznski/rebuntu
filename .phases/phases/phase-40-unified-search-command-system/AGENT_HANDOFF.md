# Agent Handoff — Phase 40

Do not implement Phase 40 as `grep + fzf + subprocess`.

Start by reading all normative architecture documents and inspecting existing Rebuntu search/query/command facilities. The native runtime and existing domain systems are the substrate.

The key architectural test is ownership:
- Phase 40 owns federation, query planning, result normalization, discovery, command registry/intent orchestration.
- Domain systems own their state and consequential execution.
- Phase 39 owns temporal history.
- Phase 37 owns secret material.
- Frontends consume Phase 40; they do not duplicate it.

Execute numbered prompts in order unless repository evidence establishes a dependency-safe reason to combine adjacent work. Do not skip closure/audit phases merely because the UI appears functional.
