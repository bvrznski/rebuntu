# 0001 — Primary structural package is `system`

- phase: 0.0
- disposition: **ACCEPTED**
- observation: the repository's primary structural package must be named
  after its role, not the product.
- evidence: the historical spec `PHASES/0.1.md` defines the primary package as
  `src/system/` with the SYSTEM → MODULE → UNIT taxonomy. The project mandate
  confirms "use `src/system`, not `src/rebuntu`".
- decision: the primary package is `src/system/`. `src/` is **not**
  created. Rebuntu is the *project*; `system` is the *structural package*.
- reconsideration trigger: only if the SYSTEM/MODULE/UNIT model is superseded.
