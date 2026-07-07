# Capability Spec: test-validation

## Purpose
Specify current automated validation scope and minimum expected checks.

## Scope
Unit-test harness behavior and identified coverage boundaries. CI workflow observations are listed separately as non-contract evidence.

## Evidence Used
- `test/Makefile.am`
- `test/breakpadwrapper_testing.cpp`
- `test/breakpadwrapper_mock.cpp`
- `test/run_ut.sh`
- `.github/workflows/L1-tests.yml`
- `.github/workflows/code-coverage.yml`

## Facts
- gtest binary `bpw_gtest.bin` is built and run by script.
- Tests rely on mocked Breakpad API classes.

## Inferences
- Existing test set mainly validates call safety (no-throw) rather than crash outcome correctness.

## Unknowns / Manual Validation Needed
- Real Breakpad crash interception and minidump persistence behavior.

## Requirements
### TVL-REQ-001
The repository test harness SHALL compile and execute gtest binary `bpw_gtest.bin`.

Evidence:
- `test/Makefile.am` defines `bin_PROGRAMS = bpw_gtest.bin`.
- `test/run_ut.sh` runs `./bpw_gtest.bin`.

#### Scenario: Unit test harness execution
- **WHEN** test prerequisites are available and `test/run_ut.sh` is executed
- **THEN** `bpw_gtest.bin` is built and run
- **AND** harness execution provides unit-test outcome status

### TVL-REQ-002
Current unit tests SHALL validate wrapper API calls for non-throw behavior with mocked Breakpad interfaces.

Evidence:
- `test/breakpadwrapper_testing.cpp` uses `EXPECT_NO_THROW` around wrapper calls.
- `test/run_ut.sh` copies mock `exception_handler.h` into include path consumed by wrapper compile.

#### Scenario: Mocked API no-throw validation
- **WHEN** mock Breakpad types are injected and wrapper API tests execute
- **THEN** selected positive/negative invocation patterns complete without thrown exceptions
- **AND** tests exercise wrapper API entry points with mock interfaces

### TVL-REQ-003
Crash-path validation SHALL include manual/integration tests because current suite does not assert real minidump creation behavior.

Evidence:
- No test code induces actual crash and verifies dump artifact.

#### Scenario: Crash-path confidence gap
- **WHEN** production onboarding requires confidence in crash dump generation
- **THEN** validation scope includes manual/integration tests beyond current unit suite
- **AND** crash-path behavior is not treated as covered by no-throw unit assertions alone

## CI Configuration Evidence (Informational)
- `.github/workflows/L1-tests.yml` configures repository CI to run `test/run_ut.sh` for pull requests to `develop`.
- `.github/workflows/code-coverage.yml` configures repository CI to run coverage mode and publish coverage artifacts.
