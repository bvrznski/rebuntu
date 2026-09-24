# input/ — Input Handling Utilities

## Purpose

Shell-native utilities for handling user input, prompts, and stdin processing.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Line reading | Reading a single line with optional prompt |
| Interactive prompts | User input with defaults in terminals |
| Terminal detection | Checking if stdin is connected to terminal |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex input parsing | Parsing category for structured formats |
| File content processing | Filesystem or text categories |
| Multi-line input handling | Bash-native heredocs or read loops |

## Examples

* `rebuntu_input_readline()` — read line with optional prompt
* `rebuntu_input_prompt()` — interactive prompt with default value
* `rebuntu_input_is_terminal()` — check if stdin is a TTY

## Dependencies

Uses native Linux utilities:
* Bash `read` builtin for input
* Test operators (`-t`) for terminal detection

## Safety Classification

| Class | Description |
|-------|-------------|
| READ_ONLY | Input reading only, no mutation |

## Pipeline Semantics

* stdout: Read line or prompt output
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors (EOF, etc.)

## Notes

For non-interactive input (piped data), these functions may behave differently.
Use `rebuntu_input_is_terminal()` to detect the context if needed.