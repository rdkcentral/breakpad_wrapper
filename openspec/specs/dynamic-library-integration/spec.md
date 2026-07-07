# Capability Spec: dynamic-library-integration

## Purpose
Specify verified and inferred integration contract for consuming native applications.

## Scope
Library artifact model, initialization path, and application linkage expectations.

## Evidence Used
- `Makefile.am`
- `configure.ac`
- `breakpad_wrapper.h`
- `breakpad_wrapper.cpp`

## Facts
- Build target name is `libbreakpadwrapper.la`.
- Shared builds are enabled and static disabled.
- Constructor-based initialization exists.

## Inferences
- Consumers are expected to use shared-library integration for centralized handler setup.

## Unknowns / Manual Validation Needed
- Final SONAME and installed `.so` symlink names.
- Header install location for SDK consumers.

## Requirements
### DLI-REQ-001
The project SHALL define wrapper library build target `libbreakpadwrapper.la`.

Evidence:
- `Makefile.am` includes `lib_LTLIBRARIES = libbreakpadwrapper.la`.

#### Scenario: Wrapper library target presence
- **WHEN** autotools build configuration is generated and `make` runs
- **THEN** libtool target `libbreakpadwrapper.la` is built from wrapper source
- **AND** wrapper library output corresponds to top-level library target definition

### DLI-REQ-002
The project SHALL configure build mode for shared libraries and disable static library generation.

Evidence:
- `configure.ac` contains `AC_ENABLE_SHARED` and `AC_DISABLE_STATIC`.

#### Scenario: Shared-only build mode
- **WHEN** `./configure` runs with default project settings
- **THEN** shared-library mode is enabled and static mode is disabled
- **AND** build artifacts are generated according to those mode settings

### DLI-REQ-003
The wrapper SHALL support integration once per process as a shared component to centralize Breakpad handler setup.

Evidence:
- Constructor-driven setup and singleton guard in `breakpad_wrapper.cpp`; shared target model from build files.

#### Scenario: Shared integration path
- **WHEN** multiple native components in the same process call wrapper APIs through shared linkage
- **THEN** handler setup logic is centralized through one wrapper implementation path
- **AND** per-process initialization flow remains aligned with constructor/singleton behavior

