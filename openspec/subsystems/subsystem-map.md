# Subsystem Map

## Purpose
Map functional subsystems and boundaries of breakpad_wrapper for onboarding.

## Scope
Repository-local runtime, API, build, and validation subsystems.

## Evidence Used
- `breakpad_wrapper.cpp`
- `breakpad_wrapper.h`
- `Makefile.am`
- `configure.ac`
- `test/Makefile.am`
- `test/run_ut.sh`

## Facts
- API subsystem SHALL expose C-callable wrapper entry points declared in `breakpad_wrapper.h`.
- Handler subsystem SHALL hold process-global handler state in static `excHandler` and initialize via `breakpad_ExceptionHandler`.
- Descriptor-routing subsystem SHALL select descriptor source from compile-time branch `MINIDUMP_RDKV`, optional `/tmp/.SecureDumpDisable`, and optional `BREAKPAD_FD`.
- Build subsystem SHALL produce libtool target `libbreakpadwrapper.la` via autotools.
- Test subsystem SHALL define gtest target `bpw_gtest.bin` and a harness script (`test/run_ut.sh`) that builds/runs it with mocked Breakpad interfaces.

## Inferences
- Integration subsystem SHOULD be consumed as a shared library in native RDK applications.
- The component MAY be treated as a thin adapter over Google Breakpad rather than a full crash-management stack.

## Unknowns / Manual Validation Needed
- Precise install/export location for public header in packaging.
- Whether consumer linkers require explicit symbol visibility tuning beyond current defaults.
