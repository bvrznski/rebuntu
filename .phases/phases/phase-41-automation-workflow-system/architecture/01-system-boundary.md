# System Boundary
Phase 41 owns durable automation/workflow orchestration: triggers, schedules, conditions, DAG execution, workflow state, retry/recovery, compensation and typed action orchestration. Domain systems retain domain state and mutation ownership.

Canonical flow:
`Phase 39 events / schedules / conditions / operator → Phase 41 → Phase 40 typed CommandIntent → domain owner → observe → plan → validate → authorize → execute → verify → Phase 39 record`.

Never degrade the workflow engine into `bash -c` on steroids.
