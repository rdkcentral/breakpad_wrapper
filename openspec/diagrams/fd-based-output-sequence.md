# FD-Based Output Sequence

## Purpose
Show verified and inferred behavior for `BREAKPAD_FD` controlled output path.

## Scope
`MINIDUMP_RDKV` code branch handling of env var and descriptor construction.

## Evidence Used
- `breakpad_wrapper.cpp`: `#ifdef MINIDUMP_RDKV` section
- `breakpad_wrapper.cpp`: `getenv("BREAKPAD_FD")`, `atoi`, descriptor constructors

## Facts
- Wrapper SHALL check `BREAKPAD_FD` only in `MINIDUMP_RDKV` builds.
- When `BREAKPAD_FD` is set, wrapper SHALL use fd-based descriptor constructor.
- When `BREAKPAD_FD` is unset, wrapper SHALL use path-based descriptor logic.

## Inferences
- Invalid numeric conversion effects are inferred from `atoi` semantics, not wrapper validation.

## Unknowns / Manual Validation Needed
- Runtime behavior when fd is invalid/unwritable/closed.
- Any fallback semantics inside real Breakpad implementation.

```mermaid
sequenceDiagram
    participant App as Application Process
    participant Lib as breakpad_wrapper
    participant Env as Environment
    participant BP as Breakpad ExceptionHandler

    App->>Lib: breakpad_ExceptionHandler()
    Lib->>Env: getenv("BREAKPAD_FD") [MINIDUMP_RDKV]
    alt BREAKPAD_FD present
        Lib->>Lib: fd = atoi(BREAKPAD_FD)
        Lib->>BP: ExceptionHandler(MinidumpDescriptor(fd), ...)
    else BREAKPAD_FD absent
        Lib->>Lib: choose minidump path (/opt/secure/minidumps or /opt/minidumps)
        Lib->>BP: ExceptionHandler(MinidumpDescriptor(path), ...)
    end
```
