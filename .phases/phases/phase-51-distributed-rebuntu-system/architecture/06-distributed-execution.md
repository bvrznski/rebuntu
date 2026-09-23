# Distributed Execution

Distributed execution preserves the existing lifecycle:

`intent -> resolve -> observe -> plan -> validate -> policy -> authorize -> dispatch -> target revalidate -> execute -> verify -> reconcile -> record`

No remote arbitrary-shell authority. Remote work is expressed as typed commands/capabilities/tasks/workflow steps.

Target nodes retain final local safety validation for their authoritative resources.
