# parsing/ — Parsing Utilities

## Purpose

Shell-native utilities for basic text parsing and data extraction.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Key-value extraction | Reading key=value pairs from files or input |
| Value lookup | Finding values by key in line-based format |
| CSV processing | Simple comma-separated value handling |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex grammars (JSON, YAML, XML) | Python modules for structured parsing |
| AST manipulation | Not shell-native |
| Regular expression processing | Use grep/sed/awk directly or Python |

## Examples

* `rebuntu_parse_keyvalue()` — read key=value file
* `rebuntu_parse_get_value()` — lookup value by key
* `rebuntu_csv_to_array()` — split CSV into lines

## Dependencies

Uses native Linux utilities:
* Bash parameter expansion for string manipulation
* `grep` for pattern matching
* `while read` loops for line processing

## Safety Classification

| Class | Description |
|-------|-------------|
| PURE | Text parsing without mutation |

## Pipeline Semantics

* stdout: Extracted values or parsed elements
* stderr: Error messages on failure
* Exit status: 0 for success (found), non-zero for not found

## Notes

These are lightweight parsing helpers for shell-native formats. For complex
structured data, prefer Python modules with proper parsers.