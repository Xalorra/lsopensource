# Build Environment & Toolchain Audit: NOVERA Legacy

## 1. Required Build Environment (Upstream Target)

The legacy *Lost Saga* client and server daemons are strictly designed to compile under a 32-bit Windows development toolchain.

### 1.1 Upstream Toolchain Specifications

| Subsystem / Requirement | Specification | Notes & Critical Gaps |
| :--- | :--- | :--- |
| **Target Architecture** | x86 (32-bit Little-Endian) | The codebase utilizes 32-bit pointer math and fixed struct packings. It cannot be compiled for x64 or ARM64 without breaking internal packet layouts. |
| **Operating System** | Windows 7 / 10 / 11 (or Windows Server 2008-2022) | Core systems invoke Win32 APIs, GDI+, DirectInput, and Windows socket extensions. |
| **IDE / Compiler Toolset** | Visual Studio 2010 (MSVC 10.0 / Toolset `v100`) | Newer compilers (MSVC 2017/2019/2022 `v143`) reject legacy C++ syntax without explicit compatibility toolsets. |
| **Graphics SDK** | Microsoft DirectX SDK (June 2010) | Requires `<d3d9.h>`, `<d3dx9.h>`, `<d3dx9math.h>`, `d3d9.lib`, and `d3dx9.lib`. |
| **Audio SDK** | DirectSound 8 (DirectX SDK June 2010) | Requires `<dsound.h>` and `dsound.lib`. |
| **Physics & Collision** | Opcode Library (v1.3) | Header files and static library `Opcode.lib`. |
| **Third-Party C++ Libraries** | Boost C++ (v1.44 - v1.52) | Used for thread management, shared pointers, and memory buffers. |
| **Database Server** | Microsoft SQL Server 2008 / 2012 / 2019 | Host for `LosaGame`, `LosaGame_Log`, and `LosaLogData` databases. |
| **Database Driver** | SQL Server Native Client 10.0 / 11.0 (`sqlncli`) | Required by `ac_dbagentsvr` for ODBC pooling. |

---

## 2. Proprietary Missing Dependencies & Static Libraries

The legacy project repository contains references to closed-source precompiled binaries and libraries in `#pragma comment(lib, ...)` blocks:

```cpp
#pragma comment(lib, "../../lib/LSLog.lib")
#pragma comment(lib, "../../lib/io3DEngine.Lib")
#pragma comment(lib, "../../lib/TownPortal.lib")
#pragma comment(lib, "../../lib/CrashFind.lib")
#pragma comment(lib, "../../lib/ioPac.lib")
#pragma comment(lib, "gdiplus")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dsound.lib")
```

### 2.1 Audit of Missing Proprietary Libraries

1. **`io3DEngine.lib` / `io3DEngine.dll`**:
   * *Status*: **MISSING IN CLEAN BUILDS**.
   * *Impact*: Contains the underlying C++ rendering pipeline, scene manager, skeletal animation solvers, particle systems, and UI manager. Without this library, linking fails with unresolved external symbols for all `io*` classes.
2. **`LSLog.lib`**:
   * *Status*: **MISSING IN CLEAN BUILDS**.
   * *Impact*: Logging daemon interface.
3. **`TownPortal.lib`**:
   * *Status*: **MISSING IN CLEAN BUILDS**.
   * *Impact*: Legacy lobby and town plaza networking protocol wrapper.
4. **`ioPac.lib`**:
   * *Status*: **MISSING IN CLEAN BUILDS**.
   * *Impact*: Encryption and decryption handler for `.iop` pack files (`rs.iop`, `map.iop`). Without this library, the client cannot read game textures, models, or configurations.
5. **`CrashFind.lib`**:
   * *Status*: **MISSING IN CLEAN BUILDS**.
   * *Impact*: Minidump crash reporter handler.

---

## 3. Targeted Compilation & Build Verification Record

In compliance with Phase 5 guidelines, targeted compilation testing was conducted to identify unresolved headers, toolchain mismatches, and platform incompatibilities.

### 3.1 Local Environment Inspection
* **Operating System**: Linux x86_64 (Kernel 6.12+)
* **Available Toolchains**: `gcc` (v15.2), `clang` (v19.1), `cmake` (v3.31), `wine` (v10.0), `node` (v22.18)
* **Absent Toolchains**: Native MSBuild (`dotnet msbuild`), Visual Studio C++ Compiler (`cl.exe`), Windows SDK.

### 3.2 Compilation Attempt 1: Direct Header Resolution
A targeted build verification was tested on `Main.cpp` and `stdafx.h` using Clang:

```bash
$ clang -c client/src/Main.cpp -Iclient/include
```

#### Diagnostic Output & Error Log:
```text
In file included from client/src/Main.cpp:1:
client/include/stdafx.h:12:10: fatal error: '../io3DEngine/ioPrerequisites.h' file not found
   12 | #include "../io3DEngine/ioPrerequisites.h"
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 error generated.
```

### 3.3 Compilation Attempt 2: Win32 & DirectX Header Resolution
When evaluated against Wine's Windows emulation headers (`/usr/include/wine/windows`):
```text
error: undefined identifier 'HINSTANCE'
error: undefined identifier 'WINAPI'
error: use of undeclared identifier 'DestroyWindow'
error: use of undeclared identifier 'PeekMessage'
error: use of undeclared identifier 'g_ResourceLoader'
error: cannot find -lio3DEngine
error: cannot find -lTownPortal
error: cannot find -lioPac
```

---

## 4. Root Causes for Build Infeasibility on Linux/Modern Toolchains

1. **Missing Source for Core Engine (`io3DEngine`)**:
   The legacy community repositories do not contain the C++ source files for `io3DEngine`, providing only precompiled 32-bit Windows `.lib` / `.dll` binaries.
2. **Platform Tight-Coupling**:
   The client utilizes hundreds of direct Win32 API calls (`SetFileAttributes`, `GetCurrentDirectory`, `PeekMessage`, `DispatchMessage`, `SleepEx`), which cannot compile natively under Linux or Android NDK without a compatibility abstraction layer.
3. **No Cross-Compilation Support**:
   There is no CMake, Meson, or Gradle build configuration in the repository. The build system is restricted to legacy Visual Studio `.sln` and `.vcxproj` project files.

---

## 5. Clean-Room Modern Development Environment Recommendation

To avoid the technical dead-ends of the legacy 2010 toolchain, the project must adopt a modern development environment:

```text
Target Production Stack:
├── Client Engine: Unity 2022.3 LTS / Unity 6 (Universal Render Pipeline - URP)
│   ├── Target Platforms: Android (ARM64), Windows (x64), iOS (ARM64)
│   ├── Graphics API: Vulkan, Metal, Direct3D 12
│   └── Input Pipeline: Unity New Input System (Touchscreen + Gamepad)
├── Authoritative Backend: Go (Golang 1.23+) / Rust (Tokio)
│   ├── Networking: WebSockets (Lobby/Matchmaking) + KCP/Reliable UDP (Combat)
│   ├── Architecture: Microservices / Docker Containers / Linux Host
│   └── Database: PostgreSQL 16 + Redis 7
└── CI/CD & Build Pipeline: GitHub Actions / Docker Compose
```
