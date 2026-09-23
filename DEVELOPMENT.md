# Rebuntu — Development (Phase 0.0)

## Toolchain

- **Language:** C++20 (baseline). Compiler: GCC/Clang.
- **Build:** CMake (>= 3.16) + Make. **Tests:** CTest.
- **No external C++ dependencies** in Phase 0.0. Add a dependency only when a
  concrete need justifies it (and record the justification).
- **Formatting:** `clang-format` (optional; no enforced style gate yet).
- **No Python runtime** is part of Rebuntu. Python, if ever used, is only at an
  explicit justified boundary (semantic/ML/testing), never the system runtime.

## Build & test

```bash
cd cpp
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

- Warnings are defects; do not silence them globally.
- After relevant C++ changes: configure → build → run relevant tests → full CTest
  where practical. Do not leave the tree uncompilable.

## Testing strategy

Categories: **unit** (contracts, pure logic), **integration** (CLI dispatch),
**system** (host integration — added later), **acceptance** (phase closure).
Tests must **not** mutate the host system. Use temporary roots / fixtures /
dependency injection; prefer controlled subprocesses.

## Repository conventions

- Primary structural package: `src/system/`. C++ namespace: `rebuntu::`.
- Native/Linux-specific code lives in adapters/providers, not scattered.
- `bin/` stays thin; it dispatches into the native implementation.
- `experiments/` must never become a production dependency.
- Keep the canonical tree (`__tree__.txt`) in sync: `scripts/generate_tree.sh`.

## Phase workflow (binding)

```
DISCOVER → MODEL → PLAN → MATERIALIZE → TOOLING → DOCUMENT → VERIFY → AUDIT
```

1. Inspect existing repository + `.phases/` corpus before changing anything.
2. Search for existing capability (Rebuntu, then Linux) before creating new.
3. Record architectural discoveries in `docs/discoveries/`.
4. Implement the smallest coherent missing abstraction.
5. Verify (build + tests + postconditions).
6. Audit the full diff and final tree before declaring done.
7. Report honestly: COMPLETE / PARTIAL / BLOCKED.

## Architectural discovery workflow

When a repeated pattern or gap is noticed, record a discovery record:

```
identifier · phase · date · observation/problem · evidence ·
related concepts · candidate abstraction · native mechanisms investigated ·
disposition (DISCOVERY|CANDIDATE|ACCEPTED|DEFERRED|REJECTED|SUPERSEDED) ·
rationale · reconsideration trigger
```

See `docs/discoveries/`. Generalize only when two or more independent uses
justify it.

## Commits & diff review

- Inspect the full diff; build; run relevant tests; check for accidental files,
  generated artifacts, and secrets before committing.
- One commit per completed task/phase unless told otherwise.
- Never discard unrelated changes; never commit a knowingly broken state.
