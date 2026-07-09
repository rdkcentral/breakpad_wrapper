# Capability Spec: fd-based-minidump-output

## Purpose
Specify descriptor-based dump output behavior controlled by environment variable.

## Scope
`BREAKPAD_FD` behavior under `MINIDUMP_RDKV` compile-time branch.

## Evidence Used
- `breakpad_wrapper.cpp` (`getenv("BREAKPAD_FD")`, `atoi`, descriptor constructors)

## Facts
- `BREAKPAD_FD` branch exists only in `MINIDUMP_RDKV` code path.
- Presence of env var triggers fd descriptor constructor.

## Inferences
- Non-numeric env values follow `atoi` conversion behavior.

## Unknowns / Manual Validation Needed
- Invalid fd fallback/failure behavior in real Breakpad runtime.

## Requirements
### FDM-REQ-001
When built with `MINIDUMP_RDKV`, and environment variable `BREAKPAD_FD` is present, the component SHALL construct `MinidumpDescriptor` using `atoi(BREAKPAD_FD)`.

Evidence:
- `breakpad_wrapper.cpp` checks `breakpadFd = getenv("BREAKPAD_FD")` and then `MinidumpDescriptor descriptor(atoi(breakpadFd));`.

#### Scenario: Descriptor creation from environment fd
- **WHEN** `MINIDUMP_RDKV` is enabled and `BREAKPAD_FD` is set
- **THEN** handler initialization constructs fd-based descriptor using `atoi(BREAKPAD_FD)`
- **AND** fd-based constructor path is selected instead of path-based descriptor

### FDM-REQ-002
When built with `MINIDUMP_RDKV`, and `BREAKPAD_FD` is absent, the component SHALL use path-based descriptor selection.

Evidence:
- `breakpad_wrapper.cpp` `else` branch after env check constructs `MinidumpDescriptor descriptor(minidump_path);`.

#### Scenario: Path fallback when env var absent
- **WHEN** `MINIDUMP_RDKV` is enabled and `BREAKPAD_FD` is not set
- **THEN** handler initialization uses path-based descriptor mode
- **AND** path selection follows the secure-dump branch logic

### FDM-REQ-003
When not built with `MINIDUMP_RDKV`, the component SHALL ignore `BREAKPAD_FD` behavior because the branch is excluded at compile time.

Evidence:
- `#ifdef MINIDUMP_RDKV` encloses all env-var logic; non-RDKV branch creates path descriptor directly.

#### Scenario: Compile-time exclusion of fd branch
- **WHEN** build configuration does not define `MINIDUMP_RDKV` and `BREAKPAD_FD` is set
- **THEN** wrapper behavior remains on non-RDKV path descriptor branch
- **AND** env-var-driven fd logic is not compiled into this path

### FDM-REQ-004
Integration validation SHALL include invalid and non-numeric `BREAKPAD_FD` cases because wrapper performs no explicit sanitization beyond `atoi`.

Evidence:
- `breakpad_wrapper.cpp` contains direct `atoi` call without range or format checks.

#### Scenario: Invalid descriptor input validation
- **WHEN** `BREAKPAD_FD` is set to non-numeric or malformed content
- **THEN** resulting descriptor value follows `atoi` conversion behavior
- **AND** runtime validation must verify observed behavior for invalid descriptor inputs

