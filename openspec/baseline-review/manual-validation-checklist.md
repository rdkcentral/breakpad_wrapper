# Manual Validation Checklist

## Purpose
Provide targeted validation steps for brownfield integration confidence.

## Scope
Runtime and integration checks not fully covered by current automated tests.

## Evidence Used
- Runtime behavior anchors: `breakpad_wrapper.cpp`
- Build anchors: `configure.ac`, `Makefile.am`
- Test coverage boundaries: `test/breakpadwrapper_testing.cpp`, `test/run_ut.sh`

## Facts
- Existing automated tests do not validate real crash-to-minidump flow.
- Existing automated tests use mocked Breakpad interfaces.

## Inferences
- Manual or integration test execution is required for production confidence.

## Unknowns / Manual Validation Needed
1. Successful wrapper initialization
- Verify constructor path initializes handler once and repeated call no-ops.
- Evidence anchor: `breakpad_autoconstruct`, `breakpad_ExceptionHandler`.

2. Generated shared library artifact
- Verify build outputs include expected shared artifact from `libbreakpadwrapper.la`.
- Evidence anchor: `Makefile.am`, `configure.ac`.

3. Application linking against wrapper
- Build a minimal native app linked to wrapper and confirm startup succeeds.

4. Crash-triggered minidump generation
- Induce controlled crash and verify dump creation.

5. Default minidump path behavior
- Validate `/minidumps` behavior in build without `MINIDUMP_RDKV`.

6. `BREAKPAD_FD` configured path
- In `MINIDUMP_RDKV` build, set valid descriptor and verify dump write to descriptor target.

7. `BREAKPAD_FD` invalid/missing behavior
- Missing: validate fallback to path mode.
- Invalid/non-numeric/closed fd: validate error/failure behavior and any fallback.

8. Crash callback behavior
- Confirm callback invocation and returned status propagation under success/failure conditions.

9. Test coverage gap closure
- Add integration-level assertions for real Breakpad interactions, not only no-throw checks.
