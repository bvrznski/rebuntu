# structures/ — Data Structure Helpers

## Purpose

Shell-native utilities for managing common data structures using Bash features.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Array operations | Push/pop elements, length checks |
| Map/dictionary | Key-value storage and retrieval |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex nested structures | Not shell-native; consider Python |
| Ordered sequences | Bash arrays natively |
| Type safety enforcement | C++ runtime for validation |

## Examples

* `rebuntu_array_push()` — add element to array
* `rebuntu_array_pop()` — remove and return last element
* `rebuntu_map_set()` / `rebuntu_map_get()` — map operations

## Dependencies

Uses native Linux utilities:
* Bash nameref (`declare -n`) for variable references
* Bash associative arrays (if needed)
* Parameter expansion for manipulation

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | Data structure modification |

## Pipeline Semantics

* stdout: Retrieved values (for pop/get operations)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors

## Notes

Uses Bash nameref feature for pass-by-reference semantics. Arrays and maps are
stored as environment variables with Rebuntu naming conventions.