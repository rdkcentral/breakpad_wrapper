# Facts Inferences Assumptions Unknowns

## Purpose
Separate evidence-backed truths from interpretation and open risk areas.

## Scope
Architecture and runtime claims for brownfield onboarding.

## Evidence Used
- Code/build/test/CI/doc evidence indexed in `openspec/baseline-review/evidence-index.md`.

## Facts
### Verified facts from code/build/tests
- Wrapper provides C API declarations in `breakpad_wrapper.h`.
- Constructor calls `breakpad_ExceptionHandler`.
- `breakpad_ExceptionHandler` allocates Breakpad ExceptionHandler once (global static guard).
- `breakpad_AddMappingInfo` only forwards to Breakpad when handler exists.
- `BREAKPAD_FD` and secure dump path branch are compiled only under `MINIDUMP_RDKV`.
- Build option `--enable-debug` maps to `-D_DEBUG_`, enabling `_DEBUG_`-guarded log prints in wrapper callback/handler paths.
- Top-level build target is `libbreakpadwrapper.la`; shared enabled/static disabled.
- Tests are gtest smoke tests with mocked Breakpad types and no real crash generation.

### Documentation-backed facts
- `CHANGELOG.md` states "Native component build support" in version `1.0.0`.
- GitHub workflows document native build and L1 test automation execution.

### Facts from official RDK documentation
- No official external RDK architecture/runtime document is present in this repository snapshot.
- Therefore, no additional SHALL statements are derived from official external docs in this baseline.

## Inferences
- Component is intended as a thin integration layer around Google Breakpad for RDK native user-space processes.
- Preferred consumption is likely shared-library linkage by applications.
- Thread-safe first-initialization is not guaranteed due to missing synchronization.

## Assumptions
- Consuming RDK components set any required compile definitions (for example `MINIDUMP_RDKV`) in their product build.
- Deployment environment provisions writable minidump destination paths or valid file descriptors.

## Unknowns / Manual Validation Needed
- Real crash signal interception and dump persistence behavior in target images.
- Semantics of invalid/non-numeric `BREAKPAD_FD` values under real Breakpad library.
- Header installation/export policy for downstream build integration.
