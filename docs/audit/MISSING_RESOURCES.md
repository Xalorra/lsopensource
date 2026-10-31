# MISSING RESOURCES CHECKLIST — LOST SAGA

**Workspace Path:** `/home/randhika/Destop/lostsaga`  
**Auditor:** Antigravity Forensic Engineering  
**Scope:** Concrete, Itemized Inventory of Critical Missing Resources Required for Original Lost Saga Reconstruction.

---

## 1. Daftar Kode Sumber yang Hilang (Missing Source Code)

### 1.1. Kode Sumber Client Gameplay (C++)
Di direktori `client/`, hanya ada 2 file C++ (`Main.cpp` dan `Application.cpp`) yang membentuk 356 baris launcher. Seluruh file C++ berikut **100% HILANG**:

1. **Core Gameplay & Stage:**
   - `ioPlayStage.cpp` / `ioPlayStage.h`: Pengontrol panggung arena permainan utama.
   - `ioLobbyStage.cpp` / `ioLobbyStage.h`: Pengontrol panggung lobi utama.
   - `ioPlazaStage.cpp` / `ioPlazaStage.h`: Pengontrol interaksi dan panggung Plaza bebas.
   - `ioRoomManager.cpp` / `ioRoomManager.h`: Pengelola state room dan channel permainan.
2. **Character & Hero Subsystem:**
   - `ioBaseChar.cpp` / `ioBaseChar.h`: Basis kelas seluruh karakter hero (HP, delay, status, state).
   - `ioPlayChar.cpp` / `ioPlayChar.h`: Karakter hero yang dikendalikan pemain.
   - `ioDummyChar.cpp` / `ioDummyChar.h`: Karakter boneka/dummy latihan.
   - `ioNpcChar.cpp` / `ioNpcChar.h`: Karakter non-pemain (monster dungeon, bos raid).
   - `ioUserCharInfo.cpp` / `ioUserCharInfo.h`: Struktur data hero pemain (gender, gear, slot).
3. **Equipment & Item Subsystem:**
   - `ioItem.cpp` / `ioItem.h`: Basis kelas seluruh perlengkapan.
   - `ioWeaponItem.cpp` / `ioWeaponItem.h`: Kelas senjata spesifik tiap hero.
   - `ioArmorItem.cpp` / `ioArmorItem.h`: Kelas zirah pelindung.
   - `ioHelmetItem.cpp` / `ioHelmetItem.h`: Kelas helm dan penutup kepala.
   - `ioCloakItem.cpp` / `ioCloakItem.h`: Kelas aksesoris/jubah/trinket.
   - `ioItemDropManager.cpp`: Pengelola pelepasan gear ke tanah dan looting.
4. **Combat & Skill Subsystem:**
   - `ioSkill.cpp` / `ioSkill.h`: Basis kelas seluruh skill hero.
   - `ioAttackSkill.cpp`, `ioBuffSkill.cpp`, `ioPassiveSkill.cpp`: Varian logika skill.
   - `ioSkillManager.cpp`: Pengelola slot skill (AD, AS, ASD, SD).
   - `ioComboManager.cpp`: Pengelola chain serangan kombo tombol 'D'.
5. **Network Client & Socket Subsystem:**
   - `ioSocket.cpp` / `ioSocket.h`: Pengelola soket TCP ke Main Server dan Game Server.
   - `ioUdpSocket.cpp`: Pengelola soket UDP untuk sinkronisasi P2P peer-to-peer antar-pemain.
   - `ioSP2PacketHandler.cpp`: Parser paket biner dari server game.
6. **User Interface (UI) Gameplay:**
   - `ioChatWnd.cpp`: Jendela obrolan chat.
   - `ioGaugeWnd.cpp`: Tampilan HUD HP bar dan Skill gauge bar.
   - `ioInventoryWnd.cpp`: Jendela inventaris hero dan gear.
   - `ioShopWnd.cpp`: Jendela toko dan gashapon.

---

### 1.2. Kode Sumber Engine Core (C++)
Di direktori `Source/`, hanya ada placeholder `Source/comingsoon` ("lorem") dan library biner di `Source/lib/`. 

Berdasarkan jejak simbol debug PDB (`io3DEngine.pdb`), source code engine yang hilang mencakup:
- Seluruh direktori `src/io3dengine/` (ratusan file):
  - `ioRenderSystem.cpp`, `ioRenderQueue.cpp`, `ioCamera.cpp`, `ioSceneManager.cpp`
  - `ioMeshManager.cpp`, `ioSkeletonManager.cpp`, `ioAnimationManager.cpp`
  - `ioSoundManager.cpp`, `ioOggSound.cpp`, `ioWaveFile.cpp`
  - `ioOpcodeManager.cpp` (pembungkus deteksi tabrakan Opcode)
  - `ioGUIManager.cpp`, `ioUIRenderer.cpp`, `ioFontManager.cpp`
  - `ioResourceLoader.cpp`, `ioThreadTaskManager.cpp`
- Seluruh kode sumber integrasi Flash Player DirectX:
  - `src/flashplayertodirectx/implementation/flashdx.cpp`

---

### 1.3. Kode Sumber Server Daemons (C++)
Berdasarkan jejak simbol debug PDB (`ls_relaysvr.pdb`), source code server yang hilang meliputi:
- Seluruh direktori `programming/src/ls_relaysvr/` (Logic, BaseClass, Handler, Operation).
- Seluruh direktori `programming/src/ls_gamesvr/` (Game Logic, Room Manager, Combat Sync).
- Seluruh direktori `programming/src/ac_mainsvr/` (User Login, Channeling, Auth Handler).
- Seluruh direktori `programming/src/ac_dbagentsvr/` (SQL Query Pool, Threading, Packet Parser).
- Seluruh direktori `programming/src/log/` (`iofile.cpp`, `iologdatapool.cpp`, dll.).

---

## 2. Daftar Header C++ yang Hilang (Missing Header Files)

Proses kompilasi client `client/LSClientNew.vcxproj` saat ini langsung gagal karena file header berikut tidak ada di disk:

1. **Header `io3DEngine`:**
   - `../io3DEngine/ioPrerequisites.h`
   - `../io3DEngine/io3DCommon.h`
   - `../io3DEngine/ioVertexFormat.h`
   - `../io3DEngine/ioFrameTimer.h`
   - `../io3DEngine/ioTimer.h`
   - `../io3DEngine/ioGUIManager.h`
   - `../io3DEngine/ioCamera.h`
   - `../io3DEngine/ioMeshManager.h`
   - `../io3DEngine/ioAnimationManager.h`
   - *Dan lebih dari 40 file header engine lainnya yang di-include pada `client/stdafx.h`.*
2. **Header `LSLog`:**
   - `../LSLog/include/LSLog.h`
3. **Header `TownPortal`:**
   - `../TownPortal/include/TownPortal.h`

---

## 3. Daftar Berkas Aset Asli yang Hilang (Missing Game Assets)

| Berkas / Direktori Aset | Deskripsi Kritis | Dampak Ketiadaan |
|---|---|---|
| `rs.iop` (~1.5 GB - 2.5 GB) | Paket arsip utama berisi model karakter (.mesh), animasi (.ani), tekstur (.dds), UI HUD, efek partikel, dan SFX | Client tidak dapat menginisialisasi resource (`g_ResourceLoader.AddPackFile` mengembalikan `false`) dan game keluar seketika |
| `map.iop` (~500 MB - 1.2 GB) | Paket arsip geometri peta 3D, terrain, skybox, dan boundary collision drop-zone | Tidak ada arena pertarungan, tidak ada plaza yang dapat dimuat |
| `sound/` / `bgm/` | Berkas musik latar dan voice character | Permainan sepenuhnya hening (silent) |
| Font TTF / Gulim9.fon | Font rendering engine Korea/Unicode | Teks antarmuka tidak dapat dirender |

---

## 4. Daftar Tools, SDK, & Pustaka Tertutup (Proprietary / Closed Binary)

1. **Tools yang Hilang:**
   - **ioPac Packer/Unpacker:** Tool resmi untuk membuat dan mengekstrak berkas `.iop` tidak disertakan.
   - **io3D Studio Max Exporter:** Plugin 3ds Max untuk mengekspor mesh, skeleton, dan animasi ke format proprietary `.mesh` dan `.ani`.
   - **ioUI Tool:** Tool pembuat antarmuka visual Lost Saga (`io3DEngineForUITool.lib` mengindikasikan adanya UI Editor internal yang tidak ada di repo).
2. **SDK Pihak Ketiga yang Hilang:**
   - **Microsoft DirectX 9 SDK (June 2010):** Diperlukan untuk kompilasi client di Windows.
   - **Visual C++ 2003 / 2010 MFC Runtime:** Diperlukan oleh binary engine lama (`mfc71.dll`, `mfc100.dll`).
3. **Pustaka Biner Tertutup Tanpa Source:**
   - `io3DEngine.lib` / `io3DEngine.dll`
   - `ioPac.lib` / `ioPac.dll`
   - `TownPortal.lib` / `TownPortal.dll`
   - `LSLog.lib` / `LSLog.dll`
   - `CrashFind.lib` / `CrashFind.dll`
   - `opcode.dll`
   - `SecureEngineSDK32.lib` (VMProtect/Themida wrapper)
   - `ggsrv30lib_x86_MD.lib` (AhnLab GameGuard v3.0 server library)

---

## 5. Ringkasan Kebutuhan Rekonstruksi

Untuk dapat membangun kembali Lost Saga menjadi game yang dapat dimainkan, pengembang **wajib memperoleh resource eksternal** berupa:
1. Client game Lost Saga original lengkap yang memuat file `rs.iop` dan `map.iop`.
2. Header C++ (`.h`) lengkap untuk `io3DEngine`, `LSLog`, dan `TownPortal`.
3. Source code client game lengkap (puluhan ribu baris C++) atau menggunakan client binary executable asli yang sudah dikompilasi oleh IO Entertainment.
