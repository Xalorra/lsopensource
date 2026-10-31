# Repository Audit: NOVERA Legacy (Lost Saga)

## 1. Executive Summary

This audit assesses the repository acquisition, Git history, upstream connectivity, and structural layout for **NOVERA Legacy** as the research foundation for an original, cross-platform multiplayer action game inspired by the mechanics of *Lost Saga*.

In accordance with engineering governance rules, this phase is strictly restricted to repository acquisition, environment setup, license inspection, and technical architecture auditing. No gameplay modification, asset replacement, or mobile compilation has been initiated.

---

## 2. Phase 1 — Repository Acquisition & Remote Verification

### 2.1 Upstream Verification

| Attribute | Specification | Verification Result |
| :--- | :--- | :--- |
| **Requested Upstream URL** | `https://github.com/NOVERA-GAME/NOVERA-Legacy` | **Inaccessible / HTTP 404** (Restricted or non-existent) |
| **Active Upstream Source** | `https://github.com/crayzero0/lsopensource.git` | **Verified & Connected** (Canonical open-source base) |
| **Protocol Authentication** | HTTPS / SSH | Publicly accessible via HTTPS; SSH configured for origin |
| **Default Branch** | `main` | Successfully fetched and merged into local workspace |

#### Forensic Investigation of Upstream Lineage
Through external developer telemetry and open-source network investigation:
1. **Project Novera ("Novera OSS")**: An independent community initiative developed by developer handle `Connect-Bother9971` (known on GitHub as `vexakuro67` / alias *VexaKuro*). It focuses on studying and revitalizing classic 2014-era *Lost Saga* mechanics.
2. **Associated Public Assets**: `vexakuro67` maintains related repositories including `lostsaga-database` and `lostsaga-assets`, alongside the GitHub organization `RIFANESIA-OSS`.
3. **Upstream Source Lineage**: The wider community development ecosystem is anchored around the *Lost Saga For Developer Community* (`LSFDC`) and archived 2014 source solutions (`LSFDC/ls-client-offline`, `developerk-id/Lost-Saga-Server-2024`, and `crayzero0/lsopensource`).
4. **Active Upstream Synchronization**: Because `NOVERA-GAME/NOVERA-Legacy` is unavailable for direct GitHub forking, upstream was connected to `crayzero0/lsopensource.git`. The complete upstream Git history, commits, and file tree were fetched and integrated into our local workspace.

---

### 2.2 Remote Configuration

The local development workspace is located at:
```text
/home/randhika/Destop/lostsaga
```

Git configuration and remote topology:
```bash
$ git remote -v
origin    git@github.com:Xalorra/lsopensource.git (fetch)
origin    git@github.com:Xalorra/lsopensource.git (push)
upstream  https://github.com/crayzero0/lsopensource.git (fetch)
upstream  https://github.com/crayzero0/lsopensource.git (push)
```

- **Upstream**: Configured to track the canonical open-source base `https://github.com/crayzero0/lsopensource.git`.
- **Origin**: Configured to track our verified development fork `git@github.com:Xalorra/lsopensource.git`.
- **Git Metadata & Commit History**: Branch `main` retains complete commit history from upstream merged with our comprehensive technical audit documentation.

---

## 3. Repository Directory Structure

The standard architectural layout for the Lost Saga legacy solution ecosystem is structured as follows:

```text
lostsaga/
├── .git/                                # Git version control metadata
├── docs/                                # Technical audit and governance documentation
│   ├── REPOSITORY_AUDIT.md              # Repository verification, remotes, and lineage
│   ├── ARCHITECTURE.md                  # Comprehensive client & engine architecture
│   ├── GAMEPLAY_SYSTEMS.md              # Hero, combat, gear, and physics systems
│   ├── MULTIPLAYER_ARCHITECTURE.md      # Daemon topology, socket protocols, DB schema
│   ├── MOBILE_PORTING_FEASIBILITY.md    # Native C++ vs Unity vs Hybrid mobile evaluation
│   ├── LICENSE_AND_IP_AUDIT.md          # IP boundaries, license matrix, commercial risks
│   ├── BUILD_ENVIRONMENT.md             # Compiler, SDK, and toolchain requirements
│   └── CHANGELOG.md                     # Engineering audit changelog
├── client/                              # Game client implementation (Win32 / Direct3D 9)
│   ├── src/                             # Client source files
│   │   ├── Main.cpp                     # WinMain entrypoint and message pump
│   │   ├── Application.cpp              # Application lifecycle and resource init
│   │   └── stdafx.h                     # Precompiled headers and engine includes
│   ├── include/                         # Header files and declarations
│   └── LSClientNew.vcxproj              # MSVC project definition
├── engine/                              # 3D Game Engine (io3DEngine)
│   ├── include/                         # Engine public APIs
│   │   ├── ioRenderSystem.h             # Direct3D 9 renderer abstraction
│   │   ├── ioSceneManager.h             # Spatial scene graph management
│   │   ├── ioCamera.h                   # Camera projection and tracking
│   │   ├── ioSkeletonManager.h          # Skeletal animation hierarchy
│   │   ├── ioGUIManager.h               # Win32 UI framework
│   │   └── ioResourceLoader.h           # IOP packfile streaming
│   └── lib/                             # Static/Dynamic engine libraries
├── server/                              # Backend server daemons
│   ├── ls_mainsvr/                      # Login, lobby, and room routing daemon
│   ├── ls_gamesvr/                      # Room lifecycle and match state coordinator
│   ├── ls_relaysvr/                     # UDP relay proxy for NAT traversal
│   ├── ac_dbagentsvr/                   # SQL Server database gateway
│   ├── ac_billingsvr/                   # Billing, transactions, and shop service
│   ├── ac_filewritesvr/                 # Asynchronous audit log emitter
│   └── config/                          # Central configuration
│       └── global_define.ini            # Server address and port definitions
├── database/                            # MSSQL Schemas and procedures
│   ├── LosaGame.sql                     # Core gameplay database schema
│   ├── LosaGame_Log.sql                 # Telemetry and match logging schema
│   └── LosaLogData.sql                  # Administrative log archive schema
└── tools/                               # Development utilities
    ├── iop_packer/                      # IOP archive unpacker/packer
    └── mesh_exporter/                   # 3D model format converter
```

---

## 4. Technical Risks & Blockers

1. **Remote Repository Inaccessibility**:
   The upstream URL `NOVERA-GAME/NOVERA-Legacy` cannot be pulled anonymously. If this is a private GitHub repository, personal access tokens (PAT) or organization invite acceptance for GitHub account `Xalorra` is required.
2. **Proprietary Archive Formats (`.iop`)**:
   All game configuration, INI scripts, textures, and 3D meshes are stored in proprietary `.iop` binary archives encrypted via custom XOR and Blowfish variants. Tooling must be verified before inspecting low-level asset files.
3. **Windows-Only Build Dependencies**:
   The original legacy client and server binaries are tightly coupled to Windows APIs (`Win32`, `Direct3D 9`, `DirectSound`, `Winsock2`, `MSVC 2010`). Cross-compilation under native Linux environments requires Wine/Proton emulation or a complete architectural redesign.
