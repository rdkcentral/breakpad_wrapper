# Exception Handler Flow

## Purpose
Describe verified handler initialization/control flow for runtime onboarding.

## Scope
`breakpad_ExceptionHandler`, constructor path, and handler singleton guard.

## Evidence Used
- `breakpad_wrapper.cpp`: `breakpad_autoconstruct`, `breakpad_ExceptionHandler`, static `excHandler`
- `breakpad_wrapper.h`: API declarations
- `test/breakpadwrapper_testing.cpp`: direct invocation of `breakpad_ExceptionHandler`

## Facts
- On library load, `breakpad_autoconstruct` SHALL invoke `breakpad_ExceptionHandler`.
- `breakpad_ExceptionHandler` SHALL return without re-initialization when `excHandler` is already non-null.
- Initial setup SHALL allocate `google_breakpad::ExceptionHandler` on heap and store pointer in static `excHandler`.
- No de-initialization API exists in this repository; handler pointer lifetime SHALL remain process-lifetime once allocated.

## Inferences
- Repeated explicit calls from application code SHOULD be safe for idempotent behavior in single-threaded initialization due to early-return guard.
- Thread-safe first-initialization SHOULD NOT be assumed because no mutex/atomic synchronization is visible.

## Unknowns / Manual Validation Needed
- Behavior under concurrent first-call races.
- Whether downstream code ever intentionally calls `breakpad_ExceptionHandler` before constructor completes.
- Initialization behavior when allocation of `google_breakpad::ExceptionHandler` fails.
