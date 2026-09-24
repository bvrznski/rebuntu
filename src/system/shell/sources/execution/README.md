# execution/ — Command Execution Wrappers

## Purpose

Shell-native command execution wrappers that enhance native shell commands with
Rebuntu semantics: timeouts, validation, verification, and error handling.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Timeout enforcement | Limiting command execution duration |
| Input validation | Verifying command arguments before execution |
| Postcondition verification | Checking result state after execution |
| Error handling | Consistent failure semantics across commands |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Process observation/control | Processes category |
| Command construction | Construction category |
| Pipeline composition | Flow category |

## Examples

* `rebuntu_exec_with_timeout()` — limit execution duration
* `rebuntu_exec_validate()` — validate before execute
* `rebuntu_exec_verify()` — verify postcondition after execution

## Dependencies

Uses native Linux utilities:
* `timeout` command for time limits
* Bash execution operators (`&&`, `||`)
* `$?` exit status capture

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | May execute commands that change system state |
| READ_ONLY | When wrapping observation-only commands |

## Pipeline Semantics

* stdout: Command output (if any)
* stderr: Diagnostics, validation messages
* Exit status: Command exit code or wrapper failure indicator