# Onboarding Summary

## Purpose
Summarize baseline OpenSpec artifacts produced for brownfield onboarding.

## Scope
Repository-local architecture, behavior, build, and validation baseline generated under `openspec/`.

## Evidence Used
- Baseline source evidence from code/build/test/CI files captured in `openspec/baseline-review/evidence-index.md`.
- Existing OpenSpec state inspected before generation: only `openspec/config.yaml` existed.

## Files Created
- `openspec/project.md`
- `openspec/runtime/exception-handler-flow.md`
- `openspec/runtime/minidump-generation-flow.md`
- `openspec/runtime/fd-based-output-flow.md`
- `openspec/subsystems/subsystem-map.md`
- `openspec/subsystems/public-api-analysis.md`
- `openspec/subsystems/build-and-packaging.md`
- `openspec/subsystems/test-validation.md`
- `openspec/diagrams/system-context.md`
- `openspec/diagrams/application-integration-sequence.md`
- `openspec/diagrams/crash-to-minidump-flow.md`
- `openspec/diagrams/fd-based-output-sequence.md`
- `openspec/baseline-review/evidence-index.md`
- `openspec/baseline-review/facts-inferences-assumptions-unknowns.md`
- `openspec/baseline-review/onboarding-gaps.md`
- `openspec/baseline-review/manual-validation-checklist.md`
- `openspec/specs/breakpad-exception-handler/spec.md`
- `openspec/specs/minidump-generation/spec.md`
- `openspec/specs/fd-based-minidump-output/spec.md`
- `openspec/specs/dynamic-library-integration/spec.md`
- `openspec/specs/build-and-packaging/spec.md`
- `openspec/specs/test-validation/spec.md`
- `openspec/specs/debug-build-logging/spec.md`

## Existing OpenSpec Files Preserved
- `openspec/config.yaml` (unchanged)

## Facts
- Wrapper API, initialization, minidump path/fd branches, and callback behavior are verified directly in `breakpad_wrapper.cpp` and `breakpad_wrapper.h`.
- Build target (`libbreakpadwrapper.la`) and shared/static build mode are verified in `Makefile.am` and `configure.ac`.
- Debug feature is verified: `--enable-debug` sets `-D_DEBUG_`, and `_DEBUG_` guarded logging exists in `breakpad_wrapper.cpp`.
- Test coverage profile (mocked Breakpad, no-throw API checks) is verified in `test/` sources and scripts.

## Documentation-backed Facts
- `CHANGELOG.md` records native component build support entry.
- CI workflows confirm native build and unit-test execution paths.
- CI-derived statements are segregated as automation evidence and not used as runtime/product behavior requirements.
- No official external RDK architecture/runtime documentation was included in this repository snapshot; no additional SHALL statements were derived from external RDK docs.

## Inferences
- Intended use is shared-wrapper integration for native components with centralized Breakpad setup.
- The component may be treated as a thin adapter over Google Breakpad rather than a full crash management service.

## Unknowns / Manual Validation Needed
- Real crash-to-minidump behavior in deployment targets.
- Invalid/non-numeric `BREAKPAD_FD` behavior with real Breakpad implementation.
- Header installation/export contract for consumer SDK packaging.
- Thread-safety of concurrent first-time initialization.

## Risky Or Uncertain Areas
- Runtime path/permission assumptions for `/minidumps`, `/opt/secure/minidumps`, `/opt/minidumps`.
- Descriptor-mode reliability for malformed or closed file descriptors.
- Lack of integration tests proving end-to-end crash dump generation.

## Manual Validation Checklist
Reference: `openspec/baseline-review/manual-validation-checklist.md`.
