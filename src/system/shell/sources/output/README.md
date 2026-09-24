# output/ — Output Formatting Utilities

## Purpose

Shell-native utilities for formatting and presenting output in structured ways.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Generic formatting | Custom format templates |
| Error reporting | Standardized error messages |
| Progress indication | Visual progress feedback |
| Table formatting | Tabular data presentation |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Text transformations | Text category (case, trim, etc.) |
| Data structure conversion | Python for complex serialization |
| Log management | Rebuntu logging subsystem |

## Examples

* `rebuntu_output_format()` — format output using template
* `rebuntu_output_error()` — standardized error message to stderr
* `rebuntu_output_progress()` — visual progress indicator (percent)
* `rebuntu_output_table()` — format data as table

## Dependencies

Uses native Linux utilities:
* Bash printf and echo for formatting
* Parameter expansion for string manipulation

## Safety Classification

| Class | Description |
|-------|-------------|
| PURE | Output formatting without mutation |

## Pipeline Semantics

* stdout: Formatted output (data)
* stderr: Error messages (for `rebuntu_output_error`)
* Exit status: 0 for success

## Notes

For machine-readable output, prefer structured formats that can be parsed
by downstream commands. Use error functions to separate diagnostics from data.