# Public API Analysis

## Purpose
Document externally callable API and call contracts verified from headers/source.

## Scope
API declarations and runtime behavior for entry points in wrapper code.

## Evidence Used
- Header declarations: `breakpad_wrapper.h`
- Implementations: `breakpad_wrapper.cpp` (`breakpad_AddMappingInfo`, `breakpad_ExceptionHandler`, `breakpad_autoconstruct`)
- Tests invoking API: `test/breakpadwrapper_testing.cpp`

## Facts
- API SHALL provide `extern "C"` linkage around public declarations in `breakpad_wrapper.h`.
- Header declarations include:
  - `breakpad_AddMappingInfo(char* name, char* identifier, size_t identifier_length, uintptr_t start_address, size_t mapping_size, size_t file_offset)`
  - `breakpad_ExceptionHandler(void)`
  - `breakpad_autoconstruct(void)`
- `breakpad_AddMappingInfo` SHALL call `ExceptionHandler::AddMappingInfo` only when global `excHandler` is non-null.
- `breakpad_AddMappingInfo` SHALL truncate/copy identifier bytes to `MDGUID` buffer using `std::min(sizeof(MDGUID), identifier_size)`.
- `breakpad_ExceptionHandler` SHALL return immediately if `excHandler` already exists.
- `breakpad_autoconstruct` SHALL call `breakpad_ExceptionHandler` during library load.

## Inferences
- Consumers SHOULD treat `breakpad_ExceptionHandler` as idempotent for repeated calls in normal single-threaded init.
- Consumers SHOULD call `breakpad_AddMappingInfo` only after handler setup for effective mapping registration.

## Unknowns / Manual Validation Needed
- Null pointer handling for `identifier` when `identifier_size > 0` (code path uses `memcpy`; tests do not cover that exact combination).
- ABI stability guarantees across versions.
- Whether all APIs are intentionally public/exported for all compiler visibility settings.
