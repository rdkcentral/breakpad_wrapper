# System Context Diagram

## Purpose
Show repository-verified runtime participants and boundaries.

## Scope
Application, wrapper library, Breakpad client API use, and minidump destinations.

## Evidence Used
- API surface: `breakpad_wrapper.h`
- Runtime logic: `breakpad_wrapper.cpp` (`breakpad_autoconstruct`, `breakpad_ExceptionHandler`)
- Build artifact context: `Makefile.am` (`libbreakpadwrapper.la`)

## Facts
- Wrapper SHALL expose C API consumed by native application process.
- Wrapper SHALL instantiate Google Breakpad ExceptionHandler.
- Wrapper SHALL route output to path or fd descriptor based on compile/runtime conditions.

## Inferences
- Shared-library linkage between application and wrapper is inferred from libtool shared build settings.

## Unknowns / Manual Validation Needed
- Concrete deployment/package path for shared object and headers in each RDK image.

```mermaid
flowchart LR
    App[RDK Native Application]
    Lib[breakpad_wrapper shared library\nfrom libbreakpadwrapper.la]
    BP[Google Breakpad ExceptionHandler]
    PathOut[Minidump Path Output\n/minidumps or /opt/*]
    FdOut[FD-based Output via BREAKPAD_FD\nMINIDUMP_RDKV only]

    App -->|calls C API| Lib
    Lib -->|creates handler| BP
    BP -->|writes minidump| PathOut
    BP -->|writes minidump (optional)| FdOut
```
