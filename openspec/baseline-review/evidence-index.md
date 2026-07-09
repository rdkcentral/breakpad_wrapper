# Evidence Index

## Purpose
Provide a traceable matrix from architecture/behavior claims to concrete evidence.

## Scope
Claims used across baseline docs and capability specs.

## Evidence Used
- `breakpad_wrapper.cpp`
- `breakpad_wrapper.h`
- `Makefile.am`
- `configure.ac`
- `test/breakpadwrapper_testing.cpp`
- `test/Makefile.am`
- `test/run_ut.sh`
- `cov_build.sh`
- `.github/workflows/*.yml`
- `CHANGELOG.md`

## Facts
The table below records claims with source-backed confidence.

| Claim | Evidence Type | Evidence Location | Confidence | Used In |
|---|---|---|---|---|
| Public C API exists (`breakpad_AddMappingInfo`, `breakpad_ExceptionHandler`, `breakpad_autoconstruct`) | Code/Header | `breakpad_wrapper.h` | High | `openspec/project.md`, `openspec/subsystems/public-api-analysis.md` |
| Constructor auto-initializes exception handler | Code | `breakpad_wrapper.cpp` function `breakpad_autoconstruct` | High | `openspec/project.md`, `openspec/runtime/exception-handler-flow.md` |
| Handler singleton guard via static pointer | Code | `breakpad_wrapper.cpp` static `excHandler`, check in `breakpad_ExceptionHandler` | High | `openspec/runtime/exception-handler-flow.md` |
| Non-RDKV default minidump path is `/minidumps` | Code | `breakpad_wrapper.cpp` `#else` branch in `breakpad_ExceptionHandler` | High | `openspec/runtime/minidump-generation-flow.md` |
| RDKV path defaults and `/tmp/.SecureDumpDisable` switch | Code | `breakpad_wrapper.cpp` `#ifdef MINIDUMP_RDKV` | High | `openspec/runtime/minidump-generation-flow.md` |
| `BREAKPAD_FD` env var controls fd descriptor path in RDKV branch | Code | `breakpad_wrapper.cpp` `getenv("BREAKPAD_FD")`, `atoi` constructor | High | `openspec/runtime/fd-based-output-flow.md` |
| Callback returns Breakpad `succeeded` value | Code | `breakpad_wrapper.cpp` `breakpadDumpCallback` | High | `openspec/runtime/minidump-generation-flow.md` |
| Build target is `libbreakpadwrapper.la` | Build | `Makefile.am` `lib_LTLIBRARIES` | High | `openspec/subsystems/build-and-packaging.md` |
| Build enables shared/disables static | Build | `configure.ac` `AC_ENABLE_SHARED`, `AC_DISABLE_STATIC` | High | `openspec/subsystems/build-and-packaging.md` |
| Debug build flag mapping to `_DEBUG_` | Build | `configure.ac` `AC_ARG_ENABLE([debug])`, `DEBUG_CXXFLAGS` | High | `openspec/specs/debug-build-logging/spec.md` |
| `_DEBUG_` guarded logging in handler/callback paths | Code | `breakpad_wrapper.cpp` `#ifdef _DEBUG_` sections | High | `openspec/specs/debug-build-logging/spec.md` |
| Unit tests compile wrapper with mock Breakpad API | Test/build | `test/Makefile.am`, `test/run_ut.sh`, `test/breakpadwrapper_mock.cpp` | High | `openspec/subsystems/test-validation.md` |
| CI runs unit tests via `test/run_ut.sh` | CI doc | `.github/workflows/L1-tests.yml` | High | `openspec/subsystems/test-validation.md` (CI evidence section) |
| Native CI build runs `cov_build.sh` | CI doc | `.github/workflows/native_full_build.yml` | High | `openspec/subsystems/build-and-packaging.md` (CI evidence section) |
| Native component build support is claimed in project changelog | Documentation | `CHANGELOG.md` entry "RDK-52988" | Medium | `openspec/baseline-review/facts-inferences-assumptions-unknowns.md` |

## Inferences
- Shared `.so` artifact naming and symlink details are inferred from libtool conventions, not directly listed in repository outputs.

## Unknowns / Manual Validation Needed
- Invalid `BREAKPAD_FD` operational behavior with real Breakpad implementation.
- End-to-end crash dump generation in deployment filesystem context.
