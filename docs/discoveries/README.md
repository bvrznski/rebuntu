# Architectural Discoveries

A lightweight record of architectural discoveries. This is NOT a database or a
runtime subsystem — it is documentation.

## Vocabulary

`DISCOVERY` → `CANDIDATE` → one of `ACCEPTED` / `DEFERRED` / `REJECTED` /
`SUPERSEDED`.

- **DISCOVERY** — an observation or problem noticed during work.
- **CANDIDATE** — a possible abstraction or mechanism under consideration.
- **ACCEPTED** — adopted into the architecture (with implementation evidence).
- **DEFERRED** — valid but not justified yet; reconsider when a second
  independent need appears.
- **REJECTED** — considered and declined; rationale recorded.
- **SUPERSEDED** — replaced by a later discovery.

## Record format

```
identifier · phase · date · observation/problem · evidence ·
related concepts · candidate abstraction · native mechanisms investigated ·
disposition · rationale · reconsideration trigger
```

Generalize only when two or more independent uses justify it. One use case is
usually insufficient to justify a global abstraction.
