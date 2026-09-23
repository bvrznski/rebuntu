# OS Task Model

Keep distinct: TaskIntent, TaskDefinition, TaskInstance, TaskPlan, TaskPolicyDecision, TaskExecutionRef and TaskOutcome.

Tasks may be read-only, mutating, scheduled, recurring, conditional, interactive, delegated, semantic-originated or workflow-originated. Every task retains provenance and exact requester/origin.

A task is not a shell command and must never collapse into arbitrary command text.
