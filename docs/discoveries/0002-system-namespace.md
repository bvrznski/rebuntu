# 0002 — C++ namespace is `rebuntu::`, not `system::`

- phase: 0.0
- disposition: **ACCEPTED**
- observation: `system` cannot occupy the global C++ namespace.
- evidence: `<cstdlib>`/`<stdlib.h>` declare `int system(const char*)` at global
  scope; a `namespace system` collides with the `<cstdlib>` `using ::system;`
  (build error: `'system' redeclared as different kind of entity`).
- decision: directory stays `src/system/` (structural); the C++ project
  namespace is `rebuntu::` (e.g. `rebuntu::core`, `rebuntu::cli`). Directory
  layout and language namespaces are orthogonal concerns.
- reconsideration trigger: never — the collision is a language constraint.
