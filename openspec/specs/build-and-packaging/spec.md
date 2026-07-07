# Capability Spec: build-and-packaging

## Purpose
Specify repository-verified build and packaging behavior.

## Scope
Autotools workflow, dependency handling hints, and compile-time options. CI workflow observations are segregated as non-contract evidence.

## Evidence Used
- `configure.ac`
- `Makefile.am`
- `cov_build.sh`

## Facts
- Project uses autotools/libtool.
- Build target is library-only wrapper component.
- Debug build mode is supported through `--enable-debug` mapping to `-D_DEBUG_`.

## Inferences
- External Breakpad dependency provisioning is expected in build environment.

## Unknowns / Manual Validation Needed
- Installation rule for public headers.
- Packaging split for runtime vs development files.
- Build failure behavior when external Breakpad layout differs from assumptions in `cov_build.sh`.

## Requirements
### BAP-REQ-001
The component build system SHALL be autotools/libtool based.

Evidence:
- `configure.ac` contains `AM_INIT_AUTOMAKE`, `LT_INIT`, `AM_PROG_LIBTOOL`.

#### Scenario: Autotools scaffolding generation
- **WHEN** `autoreconf --install` and `./configure` are run on repository source
- **THEN** build scaffolding is generated for autotools/libtool flow
- **AND** configuration proceeds through the autotools pipeline

### BAP-REQ-002
The component SHALL compile `breakpad_wrapper.cpp` into `libbreakpadwrapper.la`.

Evidence:
- `Makefile.am` sets `libbreakpadwrapper_la_SOURCES = breakpad_wrapper.cpp`.

#### Scenario: Library target compilation
- **WHEN** `make` runs in a configured build tree
- **THEN** `breakpad_wrapper.cpp` is compiled into `libbreakpadwrapper.la`
- **AND** wrapper library artifacts are produced by libtool

### BAP-REQ-003
Build environments SHALL provide Google Breakpad headers/sources or equivalent include path setup compatible with `cov_build.sh`.

Evidence:
- `cov_build.sh` clones Breakpad and sets `CXXFLAGS` include path to `${BREAKPAD_ROOT}/breakpad/src/`.

#### Scenario: External dependency availability
- **WHEN** wrapper build starts in an environment without Breakpad headers/sources
- **THEN** dependency setup must occur before successful compilation
- **AND** include path assumptions from `cov_build.sh` must be satisfied

### BAP-REQ-004
When configured with `--enable-debug=yes`, the build SHALL append `-D_DEBUG_` to compile flags.

Evidence:
- `configure.ac` `AC_ARG_ENABLE([debug], ...)` sets `DEBUG_CXXFLAGS="-D_DEBUG_"` for `yes`.

#### Scenario: Debug flag propagation
- **WHEN** configure is run with `--enable-debug=yes`
- **THEN** generated build flags include `-D_DEBUG_`
- **AND** the `_DEBUG_` preprocessor symbol is enabled during compilation

## CI Configuration Evidence (Informational)
- `.github/workflows/native_full_build.yml` configures repository CI to execute `cov_build.sh` on pull requests to `develop`.
