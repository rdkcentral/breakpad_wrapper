# FD-Based Output Flow

## Purpose
Document environment-variable-controlled file-descriptor output path behavior.

## Scope
`BREAKPAD_FD` logic in `MINIDUMP_RDKV` build branch only.

## Evidence Used
- `breakpad_wrapper.cpp`: `const char* breakpadFd = getenv("BREAKPAD_FD")`
- `breakpad_wrapper.cpp`: `MinidumpDescriptor descriptor(atoi(breakpadFd));`
- `breakpad_wrapper.cpp`: alternative path-based descriptor construction

## Facts
- In `MINIDUMP_RDKV` builds, if environment variable `BREAKPAD_FD` is present, wrapper SHALL construct `MinidumpDescriptor` with integer `atoi(BREAKPAD_FD)`.
- In `MINIDUMP_RDKV` builds, if `BREAKPAD_FD` is absent, wrapper SHALL use path-based descriptor selection logic.
- In non-`MINIDUMP_RDKV` builds, wrapper SHALL ignore `BREAKPAD_FD` because that branch is not compiled.

## Inferences
- `BREAKPAD_FD` content SHOULD be a decimal string accepted by `atoi`.
- Non-numeric values MAY become `0` through `atoi`, which may map to stdin fd semantics; this outcome is inferred from C library behavior, not validated here.

## Unknowns / Manual Validation Needed
- Runtime behavior for invalid, closed, or unauthorized file descriptor values.
- Whether Breakpad treats fd `0` or negative descriptors as failure or fallback.
- Whether descriptor-based path coexists with path callback metadata for post-processing.
