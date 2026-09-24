# information/ — Information and Observation Helpers

## Purpose

Shell-native utilities for querying system information, available tools, and
observing system state.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Property extraction | Reading key=value pairs from files |
| Tool availability | Checking if commands are available |
| System state queries | OS version, hostname, etc. |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| File content parsing | Parsing category for structured formats |
| Complex data aggregation | Python for complex analysis |
| Real-time monitoring | Rebuntu observation subsystem |

## Examples

* `rebuntu_info_getprop()` — extract property value from config file
* `rebuntu_info_available_tools()` — list which commands are available
* `rebuntu_info_current_state()` — get system information (hostname, OS)

## Dependencies

Uses native Linux utilities:
* `grep` for text search in files
* `command -v` or `which` for command availability
* `/etc/os-release` for OS identification
* `hostname` for host identification

## Safety Classification

| Class | Description |
|-------|-------------|
| READ_ONLY | Information querying only, no mutation |

## Pipeline Semantics

* stdout: Information output (property values, tool lists, state)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors

## Notes

These are lightweight observation helpers. For comprehensive system monitoring,
consider the Rebuntu observation subsystem instead.