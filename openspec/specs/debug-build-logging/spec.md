# Capability Spec: debug-build-logging

## Purpose
Specify compile-time debug logging behavior controlled by build configuration.

## Scope
`--enable-debug` configure option and `_DEBUG_`-guarded wrapper logs.

## Evidence Used
- `configure.ac` (`AC_ARG_ENABLE([debug])`, `DEBUG_CXXFLAGS`)
- `Makefile.am` (`AM_CXXFLAGS` includes `$(DEBUG_CXXFLAGS)`)
- `breakpad_wrapper.cpp` (`#ifdef _DEBUG_` in callback and handler setup paths)

## Facts
- Build configuration supports `--enable-debug` option.
- `--enable-debug=yes` maps to compile definition `-D_DEBUG_`.
- `_DEBUG_`-guarded logs exist in callback and handler setup code paths.

## Inferences
- Debug traces are intended for development/diagnostics and are absent in non-debug builds.

## Unknowns / Manual Validation Needed
- Runtime logging destination/collection policy in product images.

## Requirements
### DBL-REQ-001
The configure option `--enable-debug=yes` SHALL set `DEBUG_CXXFLAGS` to `-D_DEBUG_`.

Evidence:
- `configure.ac` sets `DEBUG_CXXFLAGS="-D_DEBUG_"` in the `yes` case of `AC_ARG_ENABLE([debug])`.

#### Scenario: Configure debug option mapping
- **WHEN** configure is invoked with `--enable-debug=yes`
- **THEN** generated configuration sets `DEBUG_CXXFLAGS` to include `-D_DEBUG_`
- **AND** the debug macro is available to compilation flags

### DBL-REQ-002
The build SHALL include `DEBUG_CXXFLAGS` in C++ compilation flags.

Evidence:
- `Makefile.am` defines `AM_CXXFLAGS = ... $(DEBUG_CXXFLAGS)`.

#### Scenario: Compilation flag inclusion
- **WHEN** build artifacts are generated from autotools files and C++ sources are compiled
- **THEN** debug macro flags from configure output are applied
- **AND** `AM_CXXFLAGS` consumes `DEBUG_CXXFLAGS`

### DBL-REQ-003
When `_DEBUG_` is defined at compile time, wrapper code SHALL emit debug prints in:
- `breakpadDumpCallback`
- entry/exit and existing-handler branch of `breakpad_ExceptionHandler`

Evidence:
- `breakpad_wrapper.cpp` has `#ifdef _DEBUG_` guarded `printf` statements in those locations.

#### Scenario: Runtime debug trace output
- **WHEN** wrapper is compiled with `_DEBUG_` and callback/handler setup paths execute
- **THEN** debug messages are printed by wrapper code
- **AND** the guarded print locations match the documented callback/handler paths
