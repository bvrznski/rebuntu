# flow/ — Pipeline Composition Primitives

## Purpose

Pipeline composition primitives that enable shell-native workflow construction.
The goal is to provide semantic abstractions over native shell pipes and redirections.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Clipboard integration | Cross-platform copy/paste abstraction (Wayland/X11/macOS) |
| Output redirection | Pipeline-to-file or command redirection |
| Command chaining | Conditional execution based on success/failure |
| Stderr separation | Capturing stderr separately from stdout |
| Buffering | Accumulating output before single write |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Workflow orchestration | Rebuntu runtime workflows |
| Task scheduling | systemd timers or Rebuntu schedules |
| Process management | Processes category |

## Examples

* `rebuntu_clip()` — pipe data to clipboard (abstracts platform)
* `rebuntu_pipe_to()` — redirect output with cleanup
* `rebuntu_chain_if_success()` — conditional command execution
* `rebuntu_with_stderr()` — separate stderr capture
* `rebuntu_buffer()` — accumulate and emit all at once

## Dependencies

Uses native Linux utilities:
* `wl-copy` (Wayland), `xclip`/`xsel` (X11), `pbcopy` (macOS)
* Bash redirection operators
* Temporary files where needed

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | May write to filesystem or external state |
| READ_ONLY | When used for observation only |

## Pipeline Semantics

* stdout: Primary data payload (what gets piped forward)
* stderr: Diagnostics, error messages
* Exit status: Indicates success/failure of the entire operation