# AGENTS.md

Guidance for AI coding agents working in this repository.

## Scope
- This is a Windows-only C++ EuroScope plugin project (MFC DLL).
- Keep changes minimal and localized. Avoid broad refactors in rendering-heavy files unless explicitly requested.
- Prefer linking to existing docs instead of duplicating long explanations:
  - [README.md](README.md)

## Build Environment
- IDE/toolchain: Visual Studio 2019, Platform Toolset v142.
- Language standard: C++17.
- Output type: Dynamic Library (.dll).
- Main project file: [VATCANSitu.vcxproj](VATCANSitu.vcxproj).

## Build Commands
- Developer Command Prompt for VS 2019:
  - `msbuild VATCANSitu.vcxproj /p:Configuration=Debug /p:Platform=Win32`
  - `msbuild VATCANSitu.vcxproj /p:Configuration=Release /p:Platform=Win32`
  - `msbuild VATCANSitu.vcxproj /p:Configuration=Debug /p:Platform=x64`
  - `msbuild VATCANSitu.vcxproj /p:Configuration=Release /p:Platform=x64`

## Important Configuration Notes
- Include/lib dependencies are configured in [VATCANSitu.vcxproj](VATCANSitu.vcxproj) and include EuroScope SDK headers under [lib/](lib/) plus curl headers under [curl/](curl/).
- Some x64 Debug settings use machine-local paths (for example D:\Documents\VATCANSitu\lib). If build fails on another machine, fix include/library directories first in [VATCANSitu.vcxproj](VATCANSitu.vcxproj).
- Win32 and x64 configurations differ in charset and MFC linkage. Do not normalize these settings unless explicitly requested.

## Runtime Context
- Plugin is loaded by EuroScope (not run as a standalone app).
- Entry points are in [VATCANSitu.cpp](VATCANSitu.cpp):
  - EuroScopePlugInInit
  - EuroScopePlugInExit
- Primary plugin class is [SituPlugin](SituPlugin.h), which creates the radar screen object and handles callbacks.

## Code Map
- Core radar logic/rendering: [CSiTRadar.cpp](CSiTRadar.cpp), [CSiTRadar.h](CSiTRadar.h)
- Plugin lifecycle and callback plumbing: [SituPlugin.cpp](SituPlugin.cpp), [SituPlugin.h](SituPlugin.h), [VATCANSitu.cpp](VATCANSitu.cpp)
- Tag drawing logic: [ACTag.cpp](ACTag.cpp), [ACTag.h](ACTag.h)
- Symbol/PPS drawing: [PPS.cpp](PPS.cpp), [PPS.h](PPS.h)
- Popup/menu UI: [CPopUpMenu.cpp](CPopUpMenu.cpp), [CPopUpMenu.h](CPopUpMenu.h), [TopMenu.h](TopMenu.h)
- Weather radar handling: [wxRadar.cpp](wxRadar.cpp), [wxRadar.h](wxRadar.h)
- Shared IDs/constants/colors: [constants.h](constants.h)

## Project Conventions
- Most files use #pragma once for include guards.
- Keep [pch.h](pch.h) include behavior intact; do not reshuffle precompiled-header usage casually.
- Existing code uses raw Win32/MFC/GDI object management and manual cleanup. Match local style when editing nearby code.
- Naming patterns commonly include:
  - Class names with C-prefix (example: CSiTRadar)
  - Struct names with S-prefix in some modules
  - Member fields with m_ prefix

## Safety and Pitfalls
- In exported MFC-facing functions, preserve required MFC state handling expectations documented in [VATCANSitu.cpp](VATCANSitu.cpp).
- Be careful with GDI/MFC resource lifetime; when adding pens/fonts/brushes, ensure corresponding cleanup follows surrounding style.
- Threaded/async paths exist in radar/weather code. Avoid introducing data races; preserve existing locking strategy when touching shared state.
- This repo has no automated test suite; validation is typically compile + manual EuroScope verification.

## Agent Workflow Recommendations
- Before code edits:
  - Identify target callback or draw path first in [SituPlugin.h](SituPlugin.h) and [CSiTRadar.h](CSiTRadar.h).
  - Confirm related constants in [constants.h](constants.h).
- After code edits:
  - Build at least one relevant configuration via msbuild.
  - If feature behavior changed, document manual verification steps in PR/summary.

## Out of Scope for Typical Tasks
- Do not upgrade toolset, migrate MFC usage, or replace rendering architecture unless the task explicitly asks for it.
- Do not remove legacy compatibility behaviors described in [README.md](README.md) without explicit approval.
