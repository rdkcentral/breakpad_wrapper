# Capability Spec: minidump-generation

## Purpose
Specify verified minidump destination selection and callback behavior.

## Scope
Descriptor path selection branches and callback return semantics.

## Evidence Used
- `breakpad_wrapper.cpp` (`breakpad_ExceptionHandler`, `breakpadDumpCallback`)

## Facts
- Non-`MINIDUMP_RDKV` branch uses `/minidumps` path descriptor.
- `MINIDUMP_RDKV` branch defaults to `/opt/secure/minidumps`, with optional switch to `/opt/minidumps`.
- Callback returns incoming `succeeded` value.

## Inferences
- Actual dump write success depends on filesystem permissions and runtime environment.

## Unknowns / Manual Validation Needed
- Real crash-induced file output validation.

## Requirements
### MDG-REQ-001
In builds where `MINIDUMP_RDKV` is not defined, the component SHALL initialize Breakpad with path descriptor `/minidumps`.

Evidence:
- `breakpad_wrapper.cpp` non-`MINIDUMP_RDKV` branch constructs `MinidumpDescriptor("/minidumps")`.

#### Scenario: Default non-RDKV dump path
- **WHEN** build configuration does not define `MINIDUMP_RDKV` and handler initialization executes
- **THEN** Breakpad descriptor path `/minidumps` is used
- **AND** non-RDKV path branch is selected

### MDG-REQ-002
In builds where `MINIDUMP_RDKV` is defined, the component SHALL default minidump path to `/opt/secure/minidumps`.

Evidence:
- `breakpad_wrapper.cpp` sets `minidump_path = "/opt/secure/minidumps"` inside `MINIDUMP_RDKV` branch.

#### Scenario: Secure default path in RDKV branch
- **WHEN** `MINIDUMP_RDKV` is enabled and `/tmp/.SecureDumpDisable` is absent
- **THEN** default descriptor path `/opt/secure/minidumps` is selected unless fd mode is configured
- **AND** secure-dump branch remains active

### MDG-REQ-003
In builds where `MINIDUMP_RDKV` is defined, presence of `/tmp/.SecureDumpDisable` SHALL switch path mode default to `/opt/minidumps`.

Evidence:
- `breakpad_wrapper.cpp` opens `/tmp/.SecureDumpDisable` and sets `minidump_path = "/opt/minidumps"` when file exists.

#### Scenario: Secure dump disable override
- **WHEN** `MINIDUMP_RDKV` is enabled and `/tmp/.SecureDumpDisable` exists
- **THEN** path-mode default switches to `/opt/minidumps`
- **AND** handler initialization uses the overridden path selection

### MDG-REQ-004
The callback registered with Breakpad SHALL return the `succeeded` flag it receives.

Evidence:
- `breakpadDumpCallback` returns `succeeded` directly.

#### Scenario: Callback status propagation
- **WHEN** Breakpad invokes `breakpadDumpCallback` with a `succeeded` status flag
- **THEN** callback returns the identical status value
- **AND** wrapper callback does not alter success state

