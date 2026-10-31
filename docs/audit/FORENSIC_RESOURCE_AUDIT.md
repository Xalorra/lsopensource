# FORENSIC RESOURCE AUDIT — LOST SAGA REPOSITORY

**Target Repository:** `https://github.com/Xalorra/lsopensource` (Forked from `crayzero0/lsopensource`)  
**Workspace Path:** `/home/randhika/Destop/lostsaga`  
**Audit Date:** 2026-10-31  
**Auditor:** Antigravity Forensic Engineering  
**Scope:** Forensic Verification of Physical Files, Source Trees, Binaries, Assets, and Architecture.

---

## 1. Executive Forensic Summary

Pemeriksaan forensik menyeluruh telah dilakukan terhadap repositori lokal di `/home/randhika/Destop/lostsaga`.

Hasil audit forensik membuktikan secara konklusif bahwa repositori ini **BUKAN** sebuah repositori *source code* Lost Saga yang lengkap, melainkan sebuah **arsip server privat (private server dump / leaked release pack)** yang dilengkapi dengan kerangka peluncur (*launcher stub*) minimalis di sisi client.

### Tabel Ringkasan Forensik Komponen

| Komponen | Status Forensik | Source Code | Binary / DLL | Header Files | Assets Fisik | Kelengkapan Estimasi |
|---|---|---|---|---|---|---|
| **C++ Client** | SKELETON LAUNCHER | 2 file (356 baris) | 0 | 4 file (206 baris) | 0 file | **~2%** |
| **Engine Core (`io3DEngine`)** | COMPILED BINARY ONLY | **0% (MISSING)** | 66 `.lib`, 77 `.dll` | **0% (MISSING)** | N/A | **~15%** (Binary) |
| **Original Game Assets** | COMPLETELY ABSENT | N/A | N/A | N/A | **0 file (`.iop`, mesh, ani, sound = 0)** | **0%** |
| **Server Daemons** | COMPILED BINARIES | **0% (MISSING)** | 10 `.exe` (PE32) | **0% (MISSING)** | N/A | **~25%** (Binary) |
| **Server Configs (INI/DAT)** | COMPLETE (Season 4/Garena) | N/A | 6 `.dat` | N/A | 532 `.ini` (25 MB) | **~90%** (Config) |
| **Database (MSSQL SQL)** | COMPLETE T-SQL SCHEMAS | 6 `.sql` (2.8 MB) | N/A | N/A | 142 tabel, 1097 stored procs | **~95%** (Schema) |
| **Total Rekonstruksi Mandiri** | **TIDAK DAPAT DIJALANKAN** | **~2%** | **~20%** | **<1%** | **0%** | **~5%** |

---

## 2. Inventarisasi Fisik Seluruh File Repositori

Berdasarkan pemindaian fisik rekursif (tidak termasuk metadata `.git/`), repositori memiliki total **793 file** dengan distribusi ekstensi sebagai berikut:

| Ekstensi | Jumlah File | Kategori | Lokasi Utama | Keterangan Forensik |
|---|---|---|---|---|
| `.ini` | 532 | Konfigurasi Server | `Server/Configs/`, `Server/ac_*/` | Definisi quest, skill, item, monster, mode server |
| `.dll` | 77 | Windows Dynamic Link Library | `Source/lib/`, `Server/` | Binary x86 precompiled (1998-2023) |
| `.bmp` | 68 | Bitmap UI Images | `client/res/` | Border dialog error, tombol exit, title bar web |
| `.lib` | 66 | Static / Import Library | `Source/lib/` | COFF/AR static archives x86 precompiled |
| `.bat` | 11 | Windows Batch Script | `Server/`, `Server/ac_*/` | Script start-stop daemon server |
| `.exe` | 11 | PE32 Executable | `Server/`, `client/res/` | 10 server daemon + 1 RGN utility |
| `.md` | 10 | Dokumentasi | Root, `docs/`, `Server/` | Dokumentasi teknis & disclaimer |
| `.log` | 9 | Log File Statis | `Server/` | Log exception bawaan dumper |
| `.pdb` | 7 | Program Database (Symbols) | `Source/lib/`, `Server/` | Debug symbol leaker (membuktikan path asli) |
| `.sql` | 6 | SQL Transact-SQL Script | `Database/`, `Server/` | Schema tabel dan stored procedures MSSQL |
| `.exp` | 6 | Export File | `Source/lib/` | Export table symbol linker |
| `.dat` | 6 | Binary Table Data | `Server/ac_gamesvr/config/tables/` | Binary table excavation dan practice |
| `.h` | 4 | C++ Header File | `client/` | Header launcher window Win32 |
| `.ilk` | 3 | Incremental Linker File | `Source/lib/` | Cache linker MSVC lama |
| `(no_ext)` | 2 | Teks / Lisensi | Root, `Source/` | `LICENSE` (MIT) dan `Source/comingsoon` ("lorem") |
| `.cpp` | 2 | C++ Source Code | `client/` | `Application.cpp` dan `Main.cpp` (259 & 97 baris) |
| `.ico` | 2 | Icon Windows | `client/res/` | `Admin.ico`, `Shipping.ico` |
| `.zip` | 1 | ZIP Archive | `Server/ac_mainsvr/config/` | `ls_mainsvr.zip` (kumpulan 21 file INI) |
| `.obj` | 1 | COFF Object | `Source/lib/` | `usewinhoard.obj` |
| `.sln` | 1 | Solution File | `client/` | `LSClientNew.sln` (VS 2010 / VS 2022) |
| `.vcxproj` | 1 | Project File | `client/` | `LSClientNew.vcxproj` |
| `.filters` | 1 | Project Filters | `client/` | `LSClientNew.vcxproj.filters` |
| `.rc` | 1 | Resource Script | `client/` | `LSClientNew.rc` |
| `.rc2` | 1 | Resource Script 2 | `client/res/` | `Version.rc2` |
| `.rgn` | 1 | Region Data | `client/res/` | `error_back.rgn` |
| `.txt` | 1 | Teks Referensi | `client/res/` | `배경스킨참고.txt` (Catatan bahasa Korea) |

---

## 3. Analisis Forensik Struktur Direktori

### 3.1. Direktori `client/`
- **Tujuan:** Kerangka dasar client game.
- **Kenyataan Forensik:** Hanya berisi 2 file C++ (`Main.cpp`, `Application.cpp`) dan 4 file header (`Application.h`, `resource.h`, `stdafx.h`, `VeryOftenUseDefine.h`).
- **Bukti Forensik:**
  - File `client/stdafx.h` mencoba memuat puluhan header engine eksternal:
    ```cpp
    #include "../io3DEngine/ioPrerequisites.h"
    #include "../LSLog/include/LSLog.h"
    #include "../TownPortal/include/TownPortal.h"
    #include "../io3DEngine/ioGUIManager.h"
    ...
    ```
  - Direktori `../io3DEngine`, `../LSLog`, dan `../TownPortal` **TIDAK ADA** di repositori.
  - Akibatnya, `client/` langsung menghasilkan error fatal saat dikompilasi (`fatal error C1083: Cannot open include file: '../io3DEngine/ioPrerequisites.h'`).
  - Total baris kode C++ aktual: **356 baris C++** dan **206 baris header**. Tidak ada satu pun baris logika gameplay, state machine, rendering pipeline, character system, atau network client.

### 3.2. Direktori `Source/`
- **Tujuan:** Diindikasikan sebagai tempat source code engine.
- **Kenyataan Forensik:**
  - `Source/comingsoon`: Berisi teks tunggal `"lorem\n"` (5 byte). Ini adalah bukti forensik tak terbantahkan bahwa uploader hanya membuat placeholder.
  - `Source/lib/`: Berisi 66 file `.lib` dan 77 file `.dll`. **NOL baris C++ source code.**
  - Seluruh header C++ (`.h`) yang diperlukan untuk menggunakan library ini **dihapus/tidak disertakan**.

### 3.3. Direktori `Server/`
- **Tujuan:** Server daemon dan konfigurasi game.
- **Kenyataan Forensik:**
  - Hanya berisi binary executable precompiled (PE32 Intel i386) dan file konfigurasi INI.
  - **NOL baris C++ server source code.**
  - Bukti di `Server/README.md`:
    > *"Binary Server - (Link Mega.nz)"*  
    > *"Client - (Link Google Drive)"*  
    > *"LSLog - Bypass Nprotect + Translate (Link Mega.nz)"*  
  - Dokumen ini secara eksplisit mengakui bahwa client dan server binary asli berada di luar repositori (Google Drive dan Mega.nz).

### 3.4. Direktori `Database/`
- **Tujuan:** Skrip basis data SQL Server.
- **Kenyataan Forensik:**
  - Skrip `LosaGame.sql` (814 KB) dan `Server/LosaGame.sql` (1.7 MB) memuat skema asli Lost Saga dari IO Entertainment.
  - Memuat 142 tabel dan 1.097 stored procedure, mencakup inventaris hero, rental hero, sistem quest, guild, ladder, peso, dan cash.
  - Mencapai kesesuaian 91.5% - 98% terhadap daftar query di `Server/Configs/ls_dbagent/ls_query.ini`.

---

## 4. Bukti Metadata Internal PDB (Forensic Artifact Extraction)

Melalui pembacaan metadata debug symbol pada file PDB yang tertinggal (`Source/lib/lib_Shipping/io3DEngine.pdb` dan `Server/ls_relaysvr/ls_relaysvr.pdb`), berhasil diekstrak jejak lingkungan build asli developer:

### Jejak Lingkungan Asli `io3DEngine`:
```text
d:\svn\foreign\v20160427\src\io3dengine\axisxyz.cpp
d:\svn\foreign\v20160427\src\io3dengine\cpuspeedcheck.cpp
d:\svn\foreign\v20160427\src\io3dengine\io3dengine.cpp
d:\svn\foreign\v20160427\src\io3dengine\ioanimationmanager.cpp
d:\svn\foreign\v20160427\src\io3dengine\iomeshmanager.cpp
d:\svn\foreign\v20160427\src\io3dengine\ioscenedatamanager.cpp
c:\lostsagaclient\lostsaga\programming\src\flashplayertodirectx\implementation\flashdx.cpp
c:\downloads\squish-1.11\squish.cpp
```
**Temuan:**
1. Engine dikompilasi dari branch internal Subversion (SVN): `d:\svn\foreign\v20160427\` (rilis luar negeri / foreign build tertanggal 27 April 2016).
2. Engine aslinya terdiri dari ratusan file C++ di bawah direktori `src/io3dengine/` yang telah di-strip seluruhnya dari repositori ini.

### Jejak Lingkungan Asli `ls_relaysvr`:
```text
d:\work\trunk\programming\src\ls_relaysvr\baseclass\cpu.cpp
d:\work\trunk\programming\src\ls_relaysvr\baseclass\hackcheck.cpp
d:\work\trunk\programming\src\ls_relaysvr\baseclass\handler.cpp
d:\work\trunk\programming\src\ls_relaysvr\baseclass\ioconfiguration.cpp
d:\work\trunk\programming\src\ls_relaysvr\baseclass\iorelayserverstate.cpp
d:\work\trunk\programming\src\ls_relaysvr\logic\lslogic.cpp
d:\project\lostsaga\trunk\programming\src\log\log.cpp
```
**Temuan:**
Source code server relay aslinya berada di `d:\work\trunk\programming\src\ls_relaysvr\`, dan seluruh source code tersebut **100% tidak ada** di repositori publik ini.

---

## 5. Kesimpulan Audit Sumber Daya

Repositori `Xalorra/lsopensource` **BUKAN** source code fungsional yang dapat dipakai untuk mem-build kembali Lost Saga secara mandiri. Repositori ini adalah gabungan dari:
1. Skema Database T-SQL asli yang cukup lengkap (~95%).
2. Server daemon compiled binary (PE32) era 2014-2023 tanpa source code (~25%).
3. Engine libraries compiled binary (COFF/PE) era 2009-2016 tanpa source code dan tanpa file header (~15%).
4. Client wrapper 356 baris kode yang rusak/tidak dapat dikompilasi (~2%).
5. **NOL** file aset permainan original (model 3D, animasi, tekstur, suara, peta) (0%).
