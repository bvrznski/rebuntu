# text/ — Text Transformations

## Purpose

Shell-native text transformations that work line-by-line or character-by-character,
respecting Unix composition and pipeline semantics.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Whitespace trimming | Remove leading/trailing whitespace |
| Case transformations | Upper/lower/case conversion |
| Line-based transforms | Filter, reformat lines |
| Simple string operations | Concatenation, substring, length |
| Field extraction | Cut by delimiter |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Complex parsing grammars | Use Python |
| Structured data parsing (JSON/YAML/XML) | Use Python |
| AST manipulation | Use Python |
| Pattern-based substitution (complex regex) | Consider sed/awk directly |

## Examples

* `rebuntu_text_trim()` — remove leading/trailing whitespace
* `rebuntu_text_uppercase()` / `lowercase()` — case conversion
* `rebuntu_text_join()` — join array with delimiter
* `rebuntu_text_split()` — split string by delimiter

## Dependencies

Uses native utilities:
* Bash parameter expansion (`${var#prefix}`, `${var%suffix}`)
* `tr` for character translation
* `awk`/`sed` for complex transformations (only where Bash insufficient)