# Onboarding Gaps

## Purpose
Highlight repository gaps that impact production onboarding confidence.

## Scope
Only gaps observable from current code/build/test/docs snapshot.

## Evidence Used
- `breakpad_wrapper.cpp`
- `Makefile.am`, `configure.ac`
- `test/breakpadwrapper_testing.cpp`, `test/run_ut.sh`
- `cov_build.sh`

## Facts
- No repository test performs a real induced crash and verifies minidump output.
- No test covers invalid/missing `BREAKPAD_FD` runtime semantics with real Breakpad.
- Build files do not explicitly install public headers (`include_HEADERS` absent in top-level `Makefile.am`).
- Wrapper does not expose deinit/shutdown API for handler lifecycle.

## Inferences
- Brownfield adopters SHOULD add integration validation in target image to confirm crash artifact generation paths.
- Consumer teams SHOULD verify ABI/export visibility contract before broad adoption.

## Unknowns / Manual Validation Needed
- Production-safe default dump location policy for each RDK profile.
- Multi-process/system integration expectations (ownership of dump directories and descriptor provisioning).
- Runtime dependency resolution for Google Breakpad shared/static libs in final package set.
