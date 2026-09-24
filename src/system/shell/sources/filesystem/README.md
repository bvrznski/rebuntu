# filesystem/ — Filesystem Operations

## Purpose

Shell-native filesystem operations that safely interact with files and directories,
including read/write, existence checks, and atomic operations.

## What Belongs Here

| Category | Description |
|----------|-------------|
| File reading | Safely reading file contents |
| File writing | Atomic write patterns (temp file + mv) |
| Existence verification | Checking if paths exist and are types |
| Size queries | Getting file sizes |
| Read/write permission checks | Verifying access permissions |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Path manipulation | Paths category |
| Directory traversal | Shell-native globbing or find command |
| File content parsing | Parsing category |

## Examples

* `rebuntu_fs_read()` — read file with error handling
* `rebuntu_fs_write()` — atomic write (temp file + mv)
* `rebuntu_fs_exists_type()` — check existence and type
* `rebuntu_fs_size()` — get file size in bytes

## Dependencies

Uses native Linux utilities:
* Bash test operators (`-r`, `-w`, `-e`, etc.)
* `stat` for file metadata
* Shell redirection operators

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | File writing operations |
| READ_ONLY | File reading, existence checks |

## Pipeline Semantics

* stdout: File contents (for read operations)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors