# src/units/jobs — Job Execution Instances

Job = submitted/scheduled/executing realization of work.

A Job represents a runtime instance of submitted work, distinct from:
- Task (the specification/specification)
- Process (an OS process abstraction)
- Thread (a concurrency unit)

## Distinction

```
Task
    describes bounded work
    ↓ submit
Job
    represents submitted/scheduled/executing realization
    ↓ execute
Result (outcome with status, evidence, verification)
```

See: ONTOLOGY.md Execution Chain section

Status: STRUCTURAL - This is a structural category for runtime instances.