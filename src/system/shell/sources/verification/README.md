# verification/ — Postcondition Verification Helpers

## Purpose

Shell-native utilities for verifying postconditions after operations complete.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Existence checks | Verifying paths exist |
| Content verification | Checking file contains expected text |
| State comparison | Comparing observed vs desired state |
| Output pattern matching | Regex/substring matching in output |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex semantic validation | Rebuntu verification subsystem |
| Multi-step verification sequences | Shell scripts or Python |
| Assertion libraries | Bash-native patterns suffice |

## Examples

* `rebuntu_verify_exists()` — check if path exists
* `rebuntu_verify_file_contains()` — verify file contains text
* `rebuntu_verify_state()` — compare observed vs expected state
* `rebuntu_verify_output()` — match output against pattern

## Dependencies

Uses native Linux utilities:
* Bash test operators (`[[ -e ]]`, etc.)
* `grep` for pattern matching
* Parameter expansion for string comparison

## Safety Classification

| Class | Description |
|-------|-------------|
| READ_ONLY | Verification checks only, no mutation |

## Pipeline Semantics

* stdout: None (exit code indicates verification result)
* stderr: Error messages on failure
* Exit status: 0 for success (verified), non-zero for failure (not verified)

## Notes

Verification helpers use shell-native patterns. For comprehensive postcondition
verification with detailed reporting, consider the Rebuntu verification subsystem.