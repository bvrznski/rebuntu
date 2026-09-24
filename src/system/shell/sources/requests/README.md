# requests/ — Request Primitives

## Purpose

Shell-native utilities for constructing and invoking shell-level requests.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Request building | Constructing request strings with operation, target, parameters |
| Request invocation | Invoking built requests |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex request validation | Rebuntu runtime with typed operations |
| Remote execution | Distributed subsystem |
| Typed command IR | C++ runtime |

## Examples

* `rebuntu_request_build()` — build request string from components
* `rebuntu_request_invoke()` — invoke a built request

## Dependencies

Uses native Linux utilities:
* Bash parameter expansion for string construction
* Shell command invocation for execution

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | Request invocation may perform mutations |

## Pipeline Semantics

* stdout: Response or confirmation output
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors

## Notes

These are lightweight shell-level request helpers. For robust typed requests with
proper validation and authorization, use the Rebuntu runtime with typed operations.