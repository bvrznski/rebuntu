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

### filesystem/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_fs_read(path)` | ✅ Implemented |
| `rebuntu_fs_write(path, content...)` | ✅ Implemented (atomic) |
| `rebuntu_fs_exists_type(path, [type])` | ✅ Implemented |
| `rebuntu_fs_size(path)` | ✅ Implemented |

### processes/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_process_exists(pid)` | ✅ Implemented |
| `rebuntu_process_state(pid)` | ✅ Implemented |
| `rebuntu_process_signal(pid, [sig])` | ✅ Implemented |

### time/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_time_now()` | ✅ Implemented (nanosecond precision) |
| `rebuntu_time_elapsed(start)` | ✅ Implemented |
| `rebuntu_time_format(ms)` | ✅ Implemented |
| `rebuntu_time_deadline_passed(deadline)` | ✅ Implemented |

### information/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_info_getprop(file, key)` | ✅ Implemented |
| `rebuntu_info_available_tools(cmd...)` | ✅ Implemented |
| `rebuntu_info_current_state(resource)` | ✅ Implemented |

### input/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_input_readline([prompt])` | ✅ Implemented |
| `rebuntu_input_prompt(question, [default])` | ✅ Implemented |
| `rebuntu_input_is_terminal()` | ✅ Implemented |

### output/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_output_format(fmt, ...)` | ✅ Implemented |
| `rebuntu_output_error(message)` | ✅ Implemented |
| `rebuntu_output_progress(current, total)` | ✅ Implemented |
| `rebuntu_output_table(header, rows...)` | ✅ Implemented |

### parsing/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_parse_keyvalue([file])` | ✅ Implemented |
| `rebuntu_parse_get_value(key)` | ✅ Implemented |
| `rebuntu_csv_to_array(csv)` | ✅ Implemented |

### security/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_security_has_capability()` | ✅ Implemented (root check) |
| `rebuntu_security_can_access(path, mode)` | ✅ Implemented |
| `rebuntu_security_require_root()` | ✅ Implemented |

### state/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_state_set(key, value...)` | ✅ Implemented |
| `rebuntu_state_get(key)` | ✅ Implemented |
| `rebuntu_state_clear()` | ✅ Implemented |

### structures/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_array_push(name, value)` | ✅ Implemented (nameref) |
| `rebuntu_array_pop(name)` | ✅ Implemented (nameref) |
| `rebuntu_map_set(name, key, value)` | ✅ Implemented (nameref) |
| `rebuntu_map_get(name, key)` | ✅ Implemented (nameref) |

### verification/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_verify_exists(path)` | ✅ Implemented |
| `rebuntu_verify_file_contains(path, text)` | ✅ Implemented |
| `rebuntu_verify_state(actual, expected)` | ✅ Implemented |
| `rebuntu_verify_output(output, pattern)` | ✅ Implemented |

### execution/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_exec_with_timeout([seconds], command...)` | ✅ Implemented |
| `rebuntu_exec_validate(command, ...args)` | ✅ Implemented |
| `rebuntu_exec_verify(cmd, verifier)` | ✅ Implemented |

### coordination/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_coord_with_lock(lockfile, command...)` | ✅ Implemented (flock) |
| `rebuntu_coord_atomic_group(command...)` | ✅ Implemented |

### construction/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_construct_command(op, ...args)` | ✅ Implemented |
| `rebuntu_escape_arg(value)` | ✅ Implemented (printf %q) |
| `rebuntu_quote_args(...values)` | ✅ Implemented |

### administration/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_admin_service_status(service)` | ✅ Implemented |
| `rebuntu_admin_user_exists(username)` | ✅ Implemented |
| `rebuntu_admin_group_members(groupname)` | ✅ Implemented |

### configuration/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_config_get(key, [default])` | ✅ Implemented |
| `rebuntu_config_exists(key)` | ✅ Implemented |
| `rebuntu_env_get(name, [default])` | ✅ Implemented |

### requests/ ✅ IMPLEMENTED

| Function | Status |
|----------|--------|
| `rebuntu_request_build(op, ...options)` | ✅ Implemented |
| `rebuntu_request_invoke(request)` | ✅ Implemented |

## Test Coverage

| Category | Tests | Status |
|----------|-------|--------|
| paths/ | test_paths.sh | ✅ Implemented |
| text/ | test_text.sh | ✅ Implemented |
| flow/ | test_flow.sh | ⚠️ Pending manual testing |
| filesystem/ | test_fs.sh | ⚠️ Pending verification |
| processes/ | test_processes.sh | ⚠️ Pending verification |
| time/ | test_time.sh | ⚠️ Pending verification |
| information/ | test_info.sh | ⚠️ Pending verification |
| input/ | test_input.sh | ⚠️ Pending verification |
| output/ | test_output.sh | ⚠️ Pending verification |
| parsing/ | test_parsing.sh | ⚠️ Pending verification |
| security/ | test_security.sh | ⚠️ Pending verification |
| state/ | test_state.sh | ⚠️ Pending verification |
| structures/ | test_structures.sh | ⚠️ Pending verification |
| verification/ | test_verification.sh | ⚠️ Pending verification |
| execution/ | test_exec.sh | ⚠️ Pending verification |
| coordination/ | test_coord.sh | ⚠️ Pending verification |
| construction/ | - | 🟡 No tests yet |
| administration/ | - | 🟡 No tests yet |
| configuration/ | - | 🟡 No tests yet |
| information/ | - | 🟡 No tests yet |
| requests/ | test_requests.sh | ⚠️ Pending verification |

## Categories with Shell Source Implementation

* **paths/** — Path normalization, canonicalization, joining (7 functions)
* **text/** — Trim, case conversion, join/split (8 functions)
* **flow/** — Clipboard integration (cross-platform), command chaining (5 functions)
* **filesystem/** — File read/write, existence checks (4 functions)
* **processes/** — Process existence, state, signals (3 functions)
* **time/** — Timestamps, duration calculation, formatting (4 functions)
* **information/** — Property extraction, tool availability (3 functions)
* **input/** — Line reading, interactive prompts, terminal detection (3 functions)
* **output/** — Formatting, error reporting, progress indication (4 functions)
* **parsing/** — Key-value extraction, CSV processing (3 functions)
* **security/** — Capability checks, permission verification (3 functions)
* **state/** — Environment-based state storage and retrieval (3 functions)
* **structures/** — Array and map operations using nameref (4 functions)
* **verification/** — Postcondition verification helpers (4 functions)
* **execution/** — Timeout enforcement, validation, verification wrappers (3 functions)
* **coordination/** — File locking with flock (2 functions)
* **construction/** — Command construction and argument escaping (3 functions)
* **administration/** — Service status queries, user/group checks (3 functions)
* **configuration/** — Environment variable access with defaults (3 functions)
* **requests/** — Request building and invocation (2 functions)

---