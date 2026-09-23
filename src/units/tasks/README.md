# src/units/tasks — Task Specification Units

Task = bounded specification of work to be performed.

A Task should not necessarily imply:
- scheduling
- execution instance
- process
- thread
- service

## Relationship to Other Concepts

```
Task specification
    ↓ submit
Job (submitted/scheduled/executing realization)
    ↓ execute
Result (outcome with status, evidence, verification)
```

See: ONTOLOGY.md Execution Chain section

Status: STRUCTURAL - This is a structural category for work specifications.