# Minidump Generation Flow

## Purpose
Capture verified minidump descriptor selection and callback behavior.

## Scope
Minidump destination selection branches and callback return semantics in wrapper code.

## Evidence Used
- `breakpad_wrapper.cpp`: `breakpad_ExceptionHandler`, `breakpadDumpCallback`
- `breakpad_wrapper.cpp`: compile-time branch `#ifdef MINIDUMP_RDKV`

## Facts
- Without `MINIDUMP_RDKV`, handler setup SHALL use `MinidumpDescriptor("/minidumps")`.
- With `MINIDUMP_RDKV`, default descriptor path SHALL start as `/opt/secure/minidumps`.
- With `MINIDUMP_RDKV`, presence of `/tmp/.SecureDumpDisable` SHALL switch descriptor path to `/opt/minidumps`.
- Callback `breakpadDumpCallback` SHALL return the `succeeded` flag value received from Breakpad.
- Wrapper code SHALL not implement upload, symbolization, deduplication, or stackwalking logic.

## Inferences
- Callback behavior SHOULD be pass-through status reporting only; no recovery/cleanup is implemented.
- Minidump path validity and write permission SHOULD be handled externally by platform setup.

## Unknowns / Manual Validation Needed
- Actual filesystem writes under real crash conditions and target permissions.
- Behavior when configured output directory does not exist.
