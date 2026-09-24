# processes/ — Process Inspection and Control

## Purpose

Shell-native process observation and control utilities that interface with Linux
process management via procfs, signals, and native commands.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Process existence | Checking if a PID exists |
| State queries | Getting process state from /proc or ps |
| Signal sending | Sending signals to processes (kill) |
| Process inspection | Reading process metadata |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Process lifecycle management | systemd for service management |
| Process orchestration | Rebuntu runtime workflows |
| Command execution | Execution category |

## Examples

* `rebuntu_process_exists()` — check if process exists
* `rebuntu_process_state()` — get process state (R/S/D, etc.)
* `rebuntu_process_signal()` — send signal to process

## Dependencies

Uses native Linux utilities:
* `/proc` filesystem for process info
* `kill` command for signals
* `ps` as fallback for state queries

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | Sending signals may affect processes |
| READ_ONLY | Process existence and state observation |

## Pipeline Semantics

* stdout: Process information (state, metadata)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors or process not found