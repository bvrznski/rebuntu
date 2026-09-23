# Phase 46 — Natural Language Operator Interface (`ask`)

Phase 46 implements `ask` as Rebuntu's natural-language operator interface.

Supported interaction:
- `ask <natural-language request>`
- bare `ask`, which presents one minimal prompt (`ask>`) for one request and then returns to the invoking shell.

`ask` is an intent interface, not a shell, not a chat shell, not an authorization authority, and not a semantic shortcut around Phase 45.
