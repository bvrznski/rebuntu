# text/ — Text Transformations

## Purpose

Shell-native text transformation utilities that work line-by-line or character-by-character,
respecting Unix composition and pipeline semantics.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Whitespace trimming | Removing leading/trailing spaces/tabs/newlines |
| Case transformations | Uppercase, lowercase conversion |
| String joining | Combining elements with delimiter |
| String splitting | Breaking string by delimiter |
| Length calculation | Character count |
| Prefix/suffix checks | Start/ends-with verification |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex parsing grammars | Python for structured data |
| Structured data parsing (JSON/YAML) | Python module |
| AST manipulation | Not shell-native |
| File content processing | Filesystem category |

## Examples

* `rebuntu_text_trim()` — remove leading/trailing whitespace
* `rebuntu_text_uppercase()` / `rebuntu_text_lowercase()` — case conversion
* `rebuntu_text_join()` / `rebuntu_text_split()` — delimiter operations
* `rebuntu_text_length()` — character count
* `rebuntu_text_starts_with()` / `rebuntu_text_ends_with()` — prefix/suffix checks

## Dependencies

Uses native Linux utilities:
* `tr` for character translation
* Bash parameter expansion for string manipulation

## Safety Classification

| Class | Description |
|-------|-------------|
| PURE | String transformation without system mutation |

## Pipeline Semantics

* stdout: Primary transformed text output
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors