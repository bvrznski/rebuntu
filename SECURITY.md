# Rebuntu — Security (Phase 0.0)

## Posture

Rebuntu is a **C++-native, deterministic, authorization-first** system.
Security is a core architectural concern, not an add-on.

## Principles

- **Privilege is a mechanism, not an authorization.** Running as root does not
  make an action authorized. Authorization is a policy decision at the
  canonical deterministic boundary.
- **`PRIVILEGE != AUTHORIZATION`.** **`DATA != CONTROL`.**
  **`MODEL OUTPUT != AUTHORITY`.**
- **Least privilege.** Scope never silently widens from user/session context to
  system scope.
- **No shell interpolation of untrusted input.** No `user input → shell → sudo`
  or `model output → sudo` paths.
- **Secret discipline.** `SecretRef != SecretMaterial`. Plaintext secrets never
  appear in logs, diffs, prompts, model context, IPC traces, audit reports,
  error messages, or test output (except isolated synthetic fixtures).
- **Native boundaries isolate mechanism.** procfs/systemd/netlink/sysfs and
  subprocess execution live in adapters/providers, with bounded I/O, timeouts,
  cancellation, and exit/signal capture.

## Semantic / LLM security boundary

A future local semantic model is at an **explicit boundary**. It may produce
hypotheses, annotations, and recommendations. It must never:
- bypass canonical vocabulary, parsing, target resolution, validation, policy,
  authorization, Operation schemas, or verification;
- turn raw event streams into privileged execution;
- be treated as a source of observed facts or authorization.

Deterministic mechanisms reduce data **before** any model sees it.

## Reporting vulnerabilities

Report security issues privately to the project maintainers (see the repository
maintainer contact) with a clear description, reproduction steps, and affected
component. Do not post secret material or exploit payloads in public issues.

## Phase 0.0 note

No security-relevant runtime is implemented yet. This document establishes the
posture and boundaries that all future security-sensitive work must respect.
