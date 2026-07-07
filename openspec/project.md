# breakpad_wrapper Baseline

## Purpose
Provide a concise, evidence-backed OpenSpec baseline for brownfield onboarding of the RDK breakpad_wrapper component.

## Scope
This baseline covers verified architecture and behavior from repository code, build files, and tests. CI workflow files are used only as automation evidence and are segregated from runtime/build contract claims.

## Evidence Used
- Source: `breakpad_wrapper.cpp` (`breakpad_ExceptionHandler`, `breakpad_AddMappingInfo`, `breakpad_autoconstruct`, `breakpadDumpCallback`)
- Public header: `breakpad_wrapper.h` (C API declarations)
- Build: `Makefile.am`, `configure.ac`, `cov_build.sh`
- Test: `test/breakpadwrapper_testing.cpp`, `test/breakpadwrapper_mock.cpp`, `test/Makefile.am`, `test/run_ut.sh`
- Repo docs/metadata: `CHANGELOG.md`, `.github/workflows/native_full_build.yml`, `.github/workflows/L1-tests.yml`, `.github/workflows/code-coverage.yml`

## Facts
- The component SHALL provide a C-callable wrapper API with these declarations in `breakpad_wrapper.h`: `breakpad_AddMappingInfo`, `breakpad_ExceptionHandler`, `breakpad_autoconstruct`.
- The wrapper SHALL create a process-global Breakpad exception handler once per process execution path of `breakpad_ExceptionHandler` (guarded by static `excHandler` in `breakpad_wrapper.cpp`).
- The wrapper SHALL install handler initialization via ELF constructor flow (`__attribute__((constructor))` in `breakpad_autoconstruct`), which calls `breakpad_ExceptionHandler`.
- The wrapper SHALL build a libtool library target named `libbreakpadwrapper.la` (`Makefile.am`: `lib_LTLIBRARIES`).
- The autotools config SHALL enable shared and disable static (`configure.ac`: `AC_ENABLE_SHARED`, `AC_DISABLE_STATIC`).
- The autotools debug option SHALL map `--enable-debug=yes` to compile flag `-D_DEBUG_` (`configure.ac`: `AC_ARG_ENABLE` and `DEBUG_CXXFLAGS`).
- When `_DEBUG_` is compiled, wrapper code SHALL emit debug `printf` traces in callback and exception-handler setup paths (`breakpad_wrapper.cpp`).
- Unit tests SHALL compile wrapper source with mocked Breakpad interfaces (`test/Makefile.am` includes `../breakpad_wrapper.cpp`; `test/run_ut.sh` injects test `exception_handler.h`).
- With current top-level build flags, symbols follow toolchain default visibility (no `-fvisibility=hidden` in `Makefile.am`), while `breakpad_AddMappingInfo` additionally carries explicit visibility attribute in header.

## Inferences
- Consuming RDK native components SHOULD link to the built shared wrapper artifact produced from `libbreakpadwrapper.la` by libtool on Linux targets.
- The wrapper MAY reduce repeated direct Breakpad client linkage across consumers by centralizing exception-handler setup in one shared component.
- Multi-threaded repeated calls to `breakpad_ExceptionHandler` MAY have race risk because no lock is present around global `excHandler` initialization.

## Unknowns / Manual Validation Needed
- Crash-path behavior with real Google Breakpad client library (tests use mock stubs only).
- Allocation-failure behavior of `new google_breakpad::ExceptionHandler(...)` during initialization is not validated.
- ABI/versioning guarantees and package install policy for headers and `.so` symlinks in RDK integration builds.

## Architecture Summary
- Purpose: initialize and expose Breakpad exception handling for native components.
- Runtime responsibilities: initialize exception handler, optionally add mapping metadata, route minidump destination by compile-time/runtime conditions.
- Repository-scope non-goals (not implemented in observed code/build/tests): no crash upload, no cloud analysis, no deduplication, no symbol generation pipeline, no local minidump stackwalking.

## Runtime Integration Model
1. Application process loads wrapper shared library.
2. Library constructor invokes `breakpad_ExceptionHandler`.
3. `breakpad_ExceptionHandler` creates `google_breakpad::ExceptionHandler` if not yet created.
4. Application may call `breakpad_AddMappingInfo` to register mappings when handler exists.
5. On crash, Breakpad callback (`breakpadDumpCallback`) returns `succeeded`.

## Public API Summary
See `openspec/subsystems/public-api-analysis.md`.

## Minidump Generation Summary
- Default (without `MINIDUMP_RDKV`): descriptor path `/minidumps`.
- With `MINIDUMP_RDKV`: default `/opt/secure/minidumps`, switched to `/opt/minidumps` if `/tmp/.SecureDumpDisable` exists.
- With `MINIDUMP_RDKV` and `BREAKPAD_FD` set: descriptor constructed from `atoi(BREAKPAD_FD)`.

## BREAKPAD_FD Summary
`BREAKPAD_FD` behavior is compiled only in `MINIDUMP_RDKV` branch (`breakpad_wrapper.cpp`). Validation of invalid/missing descriptor runtime effects remains open.

## Build/Package Summary
See `openspec/subsystems/build-and-packaging.md`.

## Test/Validation Summary
See `openspec/subsystems/test-validation.md`.

## CI Segregation Summary
- CI workflow observations are recorded as repository automation evidence only.
- Product behavior requirements are derived from code/build/test files, not from workflow triggers.

## Supporting Documents
- Runtime: `openspec/runtime/exception-handler-flow.md`
- Runtime: `openspec/runtime/minidump-generation-flow.md`
- Runtime: `openspec/runtime/fd-based-output-flow.md`
- Subsystems: `openspec/subsystems/subsystem-map.md`
- Subsystems: `openspec/subsystems/public-api-analysis.md`
- Subsystems: `openspec/subsystems/build-and-packaging.md`
- Subsystems: `openspec/subsystems/test-validation.md`
- Diagrams: `openspec/diagrams/system-context.md`
- Diagrams: `openspec/diagrams/application-integration-sequence.md`
- Diagrams: `openspec/diagrams/crash-to-minidump-flow.md`
- Diagrams: `openspec/diagrams/fd-based-output-sequence.md`
- Baseline review: `openspec/baseline-review/evidence-index.md`

## Known Unknowns Summary
- Real crash dump file creation under runtime permissions/paths.
- Invalid `BREAKPAD_FD` handling semantics.
- Packaging/install policy for exporting header(s) to consumers.
- Behavior when `MINIDUMP_RDKV` is not/ is defined by downstream build systems.
