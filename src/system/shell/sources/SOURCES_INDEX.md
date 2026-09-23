# Shell Sources Index — Function Inventory

This is a living index of shell functions in the Rebuntu source library.

## How to Use This Index

1. **Browse by category** — see `README.md` for each category
2. **Search function names** — use `grep -r "rebuntu_" src/system/shell/sources/`
3. **Check documentation** — each function has header docs with INPUT/OUTPUT contracts

## Function Naming Convention

```text
rebuntu_<category>_<verb>[_<modifiers>]()
```

Examples:
* `rebuntu_path_normalize()` — path manipulation, normalization
* `rebuntu_text_trim()` — text manipulation, trimming
* `rebuntu_clip()` — flow primitive, clipboard

## Current Function Inventory

### paths/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_path_is_absolute(path)` | ✅ Implemented |
| `rebuntu_path_normalize(path)` | ✅ Implemented |
| `rebuntu_path_canonicalize(path)` | ✅ Implemented |
| `rebuntu_path_join(...components)` | ✅ Implemented |
| `rebuntu_path_parent(path)` | ✅ Implemented |
| `rebuntu_path_basename(path)` | ✅ Implemented |
| `rebuntu_path_exists_type(path, [type])` | ✅ Implemented |

### text/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_text_trim(string)` | ✅ Implemented |
| `rebuntu_text_uppercase(string)` | ✅ Implemented |
| `rebuntu_text_lowercase(string)` | ✅ Implemented |
| `rebuntu_text_join(delimiter, ...elements)` | ✅ Implemented |
| `rebuntu_text_split(delimiter, string)` | ✅ Implemented |
| `rebuntu_text_length(string)` | ✅ Implemented |
| `rebuntu_text_starts_with(string, prefix)` | ✅ Implemented |
| `rebuntu_text_ends_with(string, suffix)` | ✅ Implemented |

### flow/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_clip([input])` | ✅ Implemented (abstracts Wayland/X11/macOS) |
| `rebuntu_pipe_to(target, command...)` | ✅ Implemented |
| `rebuntu_chain_if_success(cmd1 cmd2 ...)` | ✅ Implemented |
| `rebuntu_with_stderr(command...)` | ✅ Implemented |
| `rebuntu_buffer()` | ✅ Implemented |

### parsing/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### input/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### output/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### filesystem/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### processes/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### execution/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### information/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### time/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### security/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### verification/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### coordination/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### construction/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### configuration/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### state/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### structures/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### administration/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

### requests/ *PLANNED*

| Function | Status |
|----------|--------|
| (pending migration) | *pending* |

## Test Coverage

| Category | Tests | Status |
|----------|-------|--------|
| paths/ | test_paths.sh | ✅ Implemented |
| text/ | test_text.sh | ✅ Implemented |
| flow/ | - | ⚠️ Pending manual testing |
| Other categories | - | 🟡 Not yet implemented |

## Categories with Shell Source Implementation

* **paths/** — Path normalization, canonicalization, joining
* **text/** — Trim, case conversion, join/split
* **flow/** — Clipboard integration (cross-platform), command chaining

---

**Note:** This index will be populated as more functions are migrated from
historical Rebuntu or implemented fresh according to the Phase 0.3 taxonomy.