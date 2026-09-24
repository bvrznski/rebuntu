# construction/ — Construction Primitives

## Purpose

Shell-native utilities for constructing commands and properly escaping arguments.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Command assembly | Building command strings from components |
| Argument escaping | Proper quoting/escaping of shell metacharacters |
| Quoted argument lists | Building space-separated quoted arguments |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Command execution | Execution category |
| Pipeline composition | Flow category |
| Complex command building | Python for structured construction |

## Examples

* `rebuntu_construct_command()` — build command from operation + args
* `rebuntu_escape_arg()` — escape single argument safely
* `rebuntu_quote_args()` — quote multiple arguments

## Dependencies

Uses native Linux utilities:
* Bash printf with `%q` format for shell escaping
* Parameter expansion for string manipulation

## Safety Classification

| Class | Description |
|-------|-------------|
| PURE | String construction without mutation |

## Pipeline Semantics

* stdout: Constructed command or escaped argument(s)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors

## Notes

Use these functions when you need to build commands dynamically. They ensure
proper shell escaping to prevent injection issues.