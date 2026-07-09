# Test Validation Analysis

## Purpose
Summarize what behavior is verified by current tests and what remains unverified.

## Scope
Unit test source and harness-script behavior. CI workflow references are recorded separately as automation evidence.

## Evidence Used
- `test/breakpadwrapper_testing.cpp`
- `test/breakpadwrapper_mock.cpp`
- `test/exception_handler.h`
- `test/Makefile.am`
- `test/run_ut.sh`
- `.github/workflows/L1-tests.yml`
- `.github/workflows/code-coverage.yml`

## Facts
- Unit test binary SHALL be built as `bpw_gtest.bin` (`test/Makefile.am`).
- Tests SHALL compile wrapper implementation directly (`../breakpad_wrapper.cpp`) with mocked Breakpad API objects (`breakpadwrapper_mock.cpp`).
- Current tests SHALL verify that selected calls do not throw (`EXPECT_NO_THROW`) for `breakpad_AddMappingInfo` negative/positive cases and one call to `breakpad_ExceptionHandler`.
- Test harness SHALL create temporary include path `../client/linux/handler/exception_handler.h` from test mock header before building.

## CI Automation Evidence (Non-Contract)
- `.github/workflows/L1-tests.yml` configures repository CI to run `test/run_ut.sh` on pull requests to `develop`.
- `.github/workflows/code-coverage.yml` configures repository CI to run `test/run_ut.sh --enable-cov` and publish coverage artifacts.

## Inferences
- Current test suite SHOULD be treated as API smoke coverage, not crash-path behavioral verification.
- Mocked ExceptionHandler behavior SHOULD not be interpreted as proof of real Breakpad runtime interactions.

## Unknowns / Manual Validation Needed
- No test validates actual process crash handling and minidump file creation.
- No test validates callback side effects or callback return handling beyond compile/run.
- No explicit test validates `BREAKPAD_FD` missing/invalid handling with real descriptor semantics.
- No integration test validates consumer application linkage against installed wrapper artifact.
