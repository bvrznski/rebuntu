# paths/ — Path Manipulation

## Purpose

Safe path manipulation utilities that handle edge cases: spaces, symlinks,
relative/absolute conversion, canonicalization.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Path normalization | Resolving `..`, `.`, `~` components |
| Canonicalization | Removing symlinks to get true path |
| Relative/absolute | Conversion between forms |
| Joining paths | Safe concatenation without duplication |
| Parent extraction | Getting directory portion |
| Basename extraction | Getting filename component |
| Existence checks | Verifying path exists and is type |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| File content operations | Filesystem category |
| Path validation logic | Parsing category (if needed) |
| Path traversal security | Security category (if needed) |
| Encoding/formatting | Text category (if general purpose) |

## Examples

* `rebuntu_path_normalize()` — resolve `..` and `.`
* `rebuntu_path_canonicalize()` — get true path
* `rebuntu_path_join()` — safe concatenation
* `rebuntu_path_is_absolute()` — check form
* `rebuntu_path_exists_type()` — existence + type verification

## Dependencies

Uses native Linux utilities:
* `readlink -f` or `realpath`
* Bash parameter expansion for manipulation

## Safety Classification

| Class | Description |
|-------|-------------|
| PURE | Path transformation without mutation |
| READ_ONLY | Path observation (existence, type) |