# Phase 6 — Command, Operation & Execution System (C++-Native)

## Status: CURRENT

This document describes the canonical architecture for Rebuntu's typed command,
operation, and execution system in Phase 6. This is a foundational layer that
enables safe, verifiable, deterministic system management.

---

## 1. Core Design Philosophy

### 1.1 Typed Command vs Shell Command

> **COMMAND != SHELL COMMAND**

A Rebuntu *command* is a typed semantic request that expresses intent through
structured data, not free-form text.

```cpp
// Typed command intent (canonical IR)
CommandIntent {
    std::string verb;              // "install"
    std::optional<std::string> subject;   // "package"
    std::optional<std::string> target;    // "curl"
    ExecutionPolicy policy;
};
```

vs.

```bash
# Shell command (presentation surface only)
apt install curl --yes
sudo systemctl restart nginx
```

### 1.2 Intent != Command

> **INTENT != COMMAND**

Intent is the semantic request from the user. A command is how that intent is
represented in a particular interface.

```text
User Request: "install curl"
    ↓
Shell Parsing (presentation surface)
    ↓
CommandIntent IR (canonical typed representation)
    ↓
Resolution to canonical Operation
    ↓
Runtime Execution
```

### 1.3 Command != Operation

> **COMMAND != OPERATION**

A *command* is an interface artifact. An *operation* is a canonical system capability.

```cpp
// Operation: canonical contract for a system action
struct FilesystemCopyOperation {
    struct Inputs {
        std::filesystem::path source;
        std::filesystem::path destination;
        bool overwrite = false;
    };
    
    struct Outputs {
        Outcome outcome;
        Evidence evidence;
    };
    
    Precondition preconditions;
    Postcondition postconditions;
    VerificationStrategy verification;
};
```

---

## 2. Canonical Execution Lifecycle

### 2.1 The Full Lifecycle Flow

```text
DISCOVER
    ↓
RESOLVE TARGET (map subject+target to concrete entity)
    ↓
OBSERVE CURRENT STATE (baseline for comparison)
    ↓
EVALUATE PRECONDITIONS (is this operation valid now?)
    ↓
PLAN (if mutating, what steps are needed?)
    ↓
AUTHORIZE (policy decision: is this allowed?)
    ↓
EXECUTE (invoke native mechanism with typed capability)
    ↓
OBSERVE RESULTING STATE (postcondition baseline)
    ↓
VERIFY POSTCONDITIONS (is desired state achieved?)
    ↓
GENERATE EVIDENCE (provenance-bearing observations)
    ↓
RESULT (outcome + evidence + verification status)
```

### 2.2 Each Stage is Essential

**Discovery & Target Resolution**
- Must distinguish between ephemeral and stable identifiers
- PID ≠ durable process identity
- Name ≠ identity (can change at exec())
- Use hardware serials, UUIDs, DMI IDs where available

**State Observation**
- Read from authoritative native sources:
  - `/proc` for processes
  - sysfs/udev for devices
  - systemd D-Bus for services
- Never parse human-readable command output as primary state source

**Precondition Evaluation**
- Must be deterministic and bounded
- May query current state but must not mutate
- Should use cached evidence where freshness permits

**Authorization Decision**
- Policy evaluation happens HERE, before execution
- Scope, privilege, and permissions all checked
- Authorization does NOT grant arbitrary bytes or shell commands

**Execution & Verification**
- Execution success ≠ Verification success
- Exit code 0 proves only exit code, not desired state achieved
- Postcondition verification is a separate, independent check

### 2.3 Result Structure

```cpp
struct CommandResult {
    core::SemanticStatus status;      // SUCCESS, FAILURE, UNKNOWN, CANCELLED
    
    std::optional<core::Outcome> outcome;
    
    std::vector<core::Evidence> evidence;  // provenance-bearing observations
    
    std::chrono::milliseconds elapsed_ms;
};
```

**Key properties:**
- `status`: semantic conclusion (not exit code!)
- `outcome`: structured result with cause if failure
- `evidence`: all observations with source provenance
- `elapsed_ms`: timing information for performance analysis

---

## 3. Native Provider Preference

### 3.1 The Hierarchy of Mechanisms

For any system action, prefer mechanisms in this order:

```text
1. Direct native API (kernel syscalls where appropriate)
2. Established C library wrapper (no shell parsing)
3. D-Bus interface (systemd, udev, etc.)
4. Kernel interface (netlink, inotify, fanotify, signalfd)
5. Bounded external process (argv-style invocation only)
```

### 3.2 Native Mechanism Mapping

| Observation/Action | Preferred Native Mechanism | PROHIBITED |
|-------------------|---------------------------|------------|
| Process enumeration | `/proc` filesystem | `ps aux`, `top` parsing |
| Service state | systemd D-Bus API | `systemctl status` parsing |
| Device info | sysfs/udev properties | `lshw`, `hwinfo`, `lsusb -v` |
| Mount points | `/proc/mounts` or `/proc/self/mountinfo` | `mount` output parsing |
| Network interfaces | netlink RTNETLINK | `ip addr` parsing |
| Kernel logs | `/dev/kmsg` or journald D-Bus | `dmesg` parsing |
| Disk info | sysfs block attributes | `lsblk`, `fdisk`, `parted` |
| CPU topology | `/proc/cpuinfo`, sysfs | `lscpu` parsing |
| Memory info | `/proc/meminfo` | `free`, `vmstat` |

### 3.3 When External Process Execution is Appropriate

External processes should only be used when:

1. No native API or established library exists
2. The external tool provides a well-defined, bounded interface
3. We invoke it argv-style with no shell interpolation

Example:
```cpp
// Correct: bounded subprocess execution
ProcessOptions opts;
opts.executable = "/usr/bin/ssh";
opts.argv = {"ssh", "user@host", "command"};
opts.timeout_ms = 30000;

ProcessResult result = executor.execute(opts);

// WRONG: shell command construction
std::string cmd = "ssh user@" + host + " " + command;
system(cmd.c_str());  // NO!
```

### 3.4 Shell Command Prohibition

> **NO SHELL COMMAND CONSTRUCTION IN CANONICAL IMPLEMENTATION**

Prohibited patterns:
```cpp
// ❌ ALL OF THESE ARE PROHIBITED:

std::system("apt install curl");  // Direct shell execution
popen("systemctl status nginx", "r");  // Shell pipe parsing
"/bin/sh -c \"rm -rf " + path + "\"";  // Dynamic command strings
```

Allowed patterns:
```cpp
// ✅ Native API or argv-style subprocess only

// Option 1: Use native API (preferred)
int fd = open(path, O_RDONLY);  // Direct system call

// Option 2: Bounded subprocess with argv
ProcessOptions opts;
opts.executable = "/usr/bin/apt";
opts.argv = {"apt", "install", "curl"};
opts.timeout_ms = 60000;
```

---

## 4. Python Semantic Candidate Boundary

### 4.1 Python's Allowed Role

Python exists ONLY at explicit, justified boundaries:

- **ML/semantic inference** (BitNet, Gordon, embeddings)
- **Research prototyping** (not production authority)
- **Testing infrastructure**
- **Narrow development tooling**

### 4.2 The Boundary Contract

```text
Shell / CLI Input
    ↓
Deterministic Parser (C++)
    ↓
CommandIntent IR (typed data structure)
    ↓
Semantic Fallback Path (if deterministic parsing fails/ambiguous)
    ↓
Python Semantic Model Output
    ↓
ModelOutputValidation (C++)
    ↓
IntentCandidate (structured, not free text!)
    ↓
Resolution to canonical Operation (C++)
    ↓
Runtime Execution (C++)
```

### 4.3 Semantic Candidate Rules

> **MODEL OUTPUT != AUTHORITY**

A Python semantic model may produce:
- `SEMANTIC_ANNOTATION`
- `HYPOTHESIS`
- `RECOMMENDATION`
- `IntentCandidate` (structured, typed)

It may NEVER produce:
- Executable shell commands
- Direct authorization decisions
- Verified state
- Policy violations

### 4.4 Validation Requirements

Every semantic candidate must be validated:
1. **operation_id** must exist in CommandRegistry
2. **subject/type** must match expected type if specified
3. **parameters** must be valid for the operation
4. **confidence** must be in [0.0, 1.0]

```cpp
IntentCandidate candidate = semantic_model_output;

if (!candidate.is_valid()) {
    return IntentResolution::make_invalid();
}

// Validate against canonical vocabulary before use
auto meta = registry.find(candidate.operation_id);
if (!meta || !meta->is_compatible_with(candidate.parameters)) {
    return IntentResolution::make_invalid();
}
```

---

## 5. Stable Target Identity

### 5.1 The Identity Problem

Linux identifiers have temporal existence:
- **PID**: reused after process exits
- **Process name**: changes at exec()
- **File path**: can be renamed/symlinked

### 5.2 Rebuntu's Solution

> **NAME != IDENTITY; PATH != IDENTITY; PID != DURABLE PROCESS IDENTITY**

Rebuntu uses:
1. **Hardware identifiers** (serial numbers, UUIDs, DMI IDs)
2. **Generated Rebuntu IDs** where Linux provides none
3. **Ephemeral handles** only for observation windowing

### 5.3 Identity Resolution Flow

```text
OBSERVE (from native source)
    ↓
RESOLVE IDENTIFIERS (map ephemeral to stable)
    ↓
NORMALIZE (apply canonical naming, deduplicate)
    ↓
VALIDATE (check constraints, invariants)
    ↓
AUTHORIZE (policy decision based on validated state)
    ↓
EXECUTE (with typed capability, not arbitrary shell)
```

### 5.4 Identity Examples

| Entity | Stable Identifier | Ephemeral Handles |
|--------|------------------|-------------------|
| Process | Rebuntu PID (generated), command hash | OS PID, process name |
| Device | Serial number, UUID, DMI ID | sysfs path, udev node |
| Service | Unit file path, unit ID | Runtime state, PIDs |

---

## 6. Verification Semantics

### 6.1 Execution vs Verification

> **EXECUTION SUCCESS != VERIFIED SEMANTIC SUCCESS**

```text
Operation: copy /foo to /bar
    ↓
Execution (copy command completes)
Exit code: 0 ✅
    ↓
Verification (postcondition check)
Is /bar equal to original /foo?
Checksum match? Timestamps correct?
    ↓
Result
{
    status: SUCCESS,  // semantic conclusion
    outcome: Outcome::success(),
    evidence: [
        Evidence{"file.copy", "/foo → /bar"},
        Evidence{"file.checksum", "match"}
    ]
}
```

### 6.2 Verification Types

| Type | Purpose | Example |
|------|---------|---------|
| **Existence** | Target exists after operation | File exists at path |
| **State equality** | State matches expected value | Checksum match, config identical |
| **Predicate evaluation** | Condition is true | Service is running |
| **Invariant check** | System invariant holds | No duplicate IDs |

### 6.3 Verification Timing

```cpp
struct TimeoutPolicy {
    std::chrono::milliseconds operation_timeout;
    std::chrono::milliseconds verification_timeout;  // Separate!
};

// Execution may complete but verification may fail
CommandResult result = execute_and_verify(operation, intent);

if (result.status == SemanticStatus::kSuccess) {
    // Both execution and verification succeeded
} else if (result.outcome->verification_status == VerificationStatus::kFailed) {
    // Operation ran but postconditions not met!
}
```

### 6.4 Evidence Chain

```text
Observed Value (from native source)
    ↓
Evidence Record (provenance + timestamp + source reference)
    ↓
Assertion/Condition Evaluation
    ↓
Verification Result (PASS/FAIL/NONE_APPLICABLE)
```

**Evidence properties:**
- **Provenance**: who, what, when, how was this observed?
- **Bounded**: limited in size and scope
- **Secret-free**: no plaintext secrets

---

## 7. Implementation Architecture

### 7.1 Key Types

```cpp
// Core contracts (cpp/include/system/core/contracts.hpp)
enum class SemanticStatus {
    kSuccess,       // Completed AND verified
    kCompleted,     // Completed but verification not applicable
    kFailure,       // Attempt ran but objective not met
    kUnknown,       // Outcome could not be determined
    kCancelled,     // Explicitly cancelled before completion
};

enum class VerificationStatus {
    kVerified,      // Postconditions verified
    kUnverified,    // Not verified (may be applicable)
    kNotApplicable, // Verification not possible/required
};

struct Evidence {
    std::string source;        // What produced this
    std::string observation;   // What was observed
    Timestamp timestamp;
    std::optional<std::string> provenance;  // How it was obtained
};
```

### 7.2 Component Ownership

| Component | Owner | Responsibility |
|-----------|-------|----------------|
| CommandRegistry | shell/ | Command metadata and mapping |
| Parser | shell/parser.cpp | Tokenization, parsing into IR |
| Resolver | shell/parser.cpp | Intent → Operation resolution |
| Executor | runtime/ | Invocation with timeout/cancellation |
| Verifier | runtime/ | Postcondition evaluation |
| Outcome/Evidence | core/ | Result structure |

### 7.3 Flow Summary

```text
Shell Input: "service restart nginx"
    ↓
shell/parser.cpp tokenize() → ["service", "restart", "nginx"]
    ↓
parse_argv() → CommandIntent { verb="restart", target="nginx" }
    ↓
resolve() → OperationId = "service.restart"
    ↓
runtime/Executor::execute(OperationId, params)
    ↓
Execute native: systemd D-Bus StartUnit()
    ↓
runtime/Verifier::verify(ServiceIsRunning("nginx"))
    ↓
Produce Evidence with provenance
    ↓
Return CommandResult { status: SUCCESS, evidence: [...] }
```

---

## 8. Acceptance Criteria

### Phase 6 Completion Checklist

- [ ] Typed command IR (`CommandIntent`) exists and is immutable
- [ ] Parser produces only typed IR, no execution
- [ ] Resolution maps intent to canonical Operation
- [ ] Native provider preference enforced (no shell parsing)
- [ ] Shell command construction prohibited in C++ implementation
- [ ] Python semantic boundary has validation layer
- [ ] Stable identity resolution implemented (PID ≠ durable ID)
- [ ] Verification is separate from execution
- [ ] Evidence chain preserves provenance and boundedness
- [ ] All operations have preconditions/postconditions
- [ ] Authorization happens before execution
- [ ] Timeout policies for both operation and verification

### Files Reference

| File | Purpose |
|------|---------|
| `src/system/shell/types.hpp` | CommandIntent, IntentKind, SideEffectClass |
| `src/system/shell/parser.cpp/hpp` | Tokenization, parsing, resolution |
| `src/system/runtime/executor.hpp` | Invocation with timeout/cancellation |
| `src/system/runtime/verifier.hpp` | Postcondition evaluation |
| `src/system/core/contracts.hpp` | SemanticStatus, Evidence, Outcome types |

---

## 9. Related Discoveries

| ID | Title | Relationship |
|----|-------|--------------|
| 0014 | Execution Runtime Roles | Runner/Executor/Dispatcher roles |
| 0026 | Phase 0.2 Operational Grammar | State dimensions, Result model |
| 0032 | Phase 0.17 Results Model | Evidence chain, verification |

---

## 10. Summary

Phase 6 establishes the foundation for safe, verifiable system management:

1. **Typed commands** instead of shell strings
2. **Canonical execution lifecycle** with distinct stages
3. **Native provider preference** (no shell parsing)
4. **Python semantic boundary** with validation
5. **Stable identity resolution** (PID ≠ durable ID)
6. **Verification semantics** separate from execution

The goal is not to prevent all shell use, but to ensure:

- No arbitrary user text becomes a privileged shell command
- All system mutations go through typed contracts
- Verification is independent from execution
- Evidence preserves provenance and enables auditing