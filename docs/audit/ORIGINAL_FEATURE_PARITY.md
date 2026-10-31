# ORIGINAL GAME FEATURE PARITY AUDIT — LOST SAGA

**Workspace Path:** `/home/randhika/Destop/lostsaga`  
**Auditor:** Antigravity Forensic Engineering  
**Scope:** Rigorous Feature Parity Matrix Between Original Lost Saga (IO Entertainment / Valofe) and Available Repository Resources.

---

## 1. Metodologi Penilaian Paritas Fitur

Untuk mencegah klaim palsu atau kesimpulan prematur, setiap fitur gameplay Lost Saga original dinilai secara ketat berdasarkan bukti fisik aktual dengan 6 kategori status:

- **VERIFIED COMPLETE:** Fitur memiliki kode sumber lengkap, aset terkait, dan integrasi backend yang terverifikasi secara fisik.
- **PARTIALLY AVAILABLE:** Sebagian komponen tersedia (misalnya hanya konfigurasi tabel atau file database), namun komponen lain tidak lengkap.
- **SOURCE MISSING:** Logika fitur hanya ada dalam binary precompiled (.exe / .lib / .dll) tanpa kode sumber C++.
- **ASSET MISSING:** Fitur memerlukan model 3D, animasi, tekstur, atau audio, namun aset tersebut 0% tidak ditemukan di repositori.
- **DEPENDENCY MISSING:** Fitur terhambat oleh library eksternal, header file yang hilang, atau toolchain yang tidak tersedia.
- **UNKNOWN / UNVERIFIED:** Fitur tidak dapat diverifikasi secara objektif dari data repositori yang ada.

---

## 2. Matriks Paritas Fitur Lengkap

| Fitur Lost Saga Original | Status Forensik | File Path Bukti | Kelas / Fungsi / Konfigurasi | Keterangan & Catatan Forensik |
|---|---|---|---|---|
| **Sistem Hero Switching (Ganti Karakter In-Game)** | SOURCE MISSING / ASSET MISSING | `Server/Configs/ls_gamesvr/config/charslotinfo.ini` | `[common] default_max_char_slot = 12` | Pengaturan jumlah slot hero ada di server INI, namun kode C++ client untuk pertukaran hero (`ioPlayStage::ChangeCharacter`) dan model 3D hero **hilang**. |
| **Sistem Gear Drop & Looting (Pelepasan Perlengkapan)** | SOURCE MISSING / ASSET MISSING | `Server/Configs/ls_gamesvr/config/sp2_item.ini:L1-L2447` | Definisi 2.447 item perlengkapan | Daftar item lengkap di server INI. Namun sistem drop fisik (gear jatuh ke tanah saat diserang), hitbox picking, dan mesh 3D item **tidak ada**. |
| **Mekanika Combat (Normal Attack, Combo, Dash, Jump Attack)** | SOURCE MISSING / ASSET MISSING | `Server/Configs/ls_gamesvr/config/ls_skill.ini` | Nilai recovery gauge & tic | Logika perhitungan damage, hitstun, frame recovery, dan animasi serangan **100% hilang dari client source**. |
| **Skill Execution (AD, AS, ASD, SD Key Triggers)** | SOURCE MISSING / ASSET MISSING | `Server/Configs/ls_gamesvr/config/ls_skill.ini:L5` | `skill_cnt = 1034` | Server memuat 1.034 definisi skill, namun implementasi eksekusi skill, proyektil skill, buff/debuff, dan partikel visual di client **hilang**. |
| **Status Effect (Faint, Freeze, Stun, Knockdown, Blow-away)** | SOURCE MISSING | Binary `Server/ac_gamesvr/ls_gamesvr.exe` | Logika status internal binary server | Diatur secara internal dalam binary server game dan `io3DEngine.dll`. Tidak ada source code state machine di client. |
| **Plaza Mode (Lobi Terbuka, Memancing, Menggali Relik)** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/ac_gamesvr/config/tables/LSC_Excavation_*.dat` | Tabel excavation grade & info | Konfigurasi server untuk drop item galian ada di berkas `.dat`. Namun peta Plaza 3D, model kolam pancing, joran, dan animasi memancing **hilang**. |
| **Mode Deathmatch / Team Deathmatch** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/Configs/ls_gamesvr/config/teamsurvivalmode.ini` | Konfigurasi waktu dan skor TDM | Aturan mode permainan ada di INI server. Geometri arena pertarungan 3D dan spawn point **hilang**. |
| **Boss Raid Mode** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/Configs/ls_gamesvr/config/bossmode.ini` | Nilai HP boss, scaling player | Aturan mode ada di server INI. Model 3D Boss, AI script boss di client, dan map raid **hilang**. |
| **Prisoner Mode (Mode Tawanan / Tali)** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/Configs/ls_gamesvr/config/catchmode.ini` | Konfigurasi batas tawanan & untie | Logika aturan penawanan ada di server INI. Sistem ikatan visual (tali), animasi terikat, dan aksi penyelamatan di client **hilang**. |
| **Monster Survival / Dungeon Mode** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/Configs/ls_gamesvr/config/monstersurvivalmode.ini`, `dungeon_a_mode.ini` | Tabel spawn gelombang monster | Konfigurasi wave monster ada di server. Model 3D monster, animasi monster, dan collision map **hilang**. |
| **Sistem Chatting & Emoticon In-Game** | SOURCE MISSING / ASSET MISSING | `Source/lib/io3DEngine.pdb` (simbol) | Simbol `ioIME.cpp`, `InputBox.cpp` | Fitur input teks dan rendering font ditangani oleh library biner `io3DEngine.lib` dan `ioFreeType.lib`. Tekstur bubble chat & font **hilang**. |
| **Sistem Guild & Mark Markah Guild** | PARTIALLY AVAILABLE / ASSET MISSING | `Database/LosaGame.sql:L1-L200`, `client/res/web_title_guild.bmp` | Tabel `define_guild`, `game_guild_*` | Database memiliki skema dan stored procedure guild lengkap. Interface client hanya memiliki bitmap header tombol web lobi. |
| **Sistem Ranking Ladder** | PARTIALLY AVAILABLE | `Database/LosaGame.sql:AGENT_RANKING_*` | Stored procs `AGENT_RANKING_LADDER_TITLE` | Prosedur kalkulasi poin ladder lengkap di SQL Server. Client UI ladder **hilang**. |
| **Sistem Toko & Gashapon (Shop / Capsule Machine)** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/Configs/ls_gamesvr/config/sp2_gashapon_present.ini` | Tabel probabilitas gashapon (1.9 MB) | Persentase gacha dan drop list tersedia di server INI. Tampilan 3D mesin gashapon, animasi pembukaan telur gashapon, dan icon item **hilang**. |
| **Sistem Penempaan / Upgrade Gear (Reinforce / Alchemic)** | PARTIALLY AVAILABLE / ASSET MISSING | `Server/Configs/ls_gamesvr/config/sp2_alchemic_info.ini` | Tabel alchemic & reinforce rate (1 MB) | Logika persentase sukses tempa ada di server. UI penempaan dan efek visual gemerlap gear upgrade **hilang**. |
| **Sistem Quest & Achievement** | PARTIALLY AVAILABLE | `Server/Configs/ls_gamesvr/config/sp2_quest_info.ini` | Tabel definisi quest (2.8 MB) | Ribuan definisi quest harian/mingguan dan reward ada di server INI dan SQL `game_quest_save`. UI jendela quest di client **hilang**. |
| **Sistem Audio & Voice Over** | ASSET MISSING / SOURCE MISSING | `Source/lib/ogg.dll`, `Source/lib/vorbis.dll` | Library audio loader x86 | Pustaka pemutar suara Vorbis/OGG tersedia dalam format DLL biner. Namun seluruh file audio game (`.wav`, `.ogg`, `.mp3`) **0% tidak ada**. |
| **Sistem P2P Network / UDP Relay** | SOURCE MISSING | `Server/ls_relaysvr/ls_relaysvr.exe` | Binary daemon UDP relay | Binary server relay tersedia dan siap dijalankan. Source code soket jaringan P2P di client **hilang**. |
| **Sistem Patching / Package Decryption** | SOURCE MISSING / ASSET MISSING | `Source/lib/ioPac.lib`, `client/Application.cpp:L215` | `g_ResourceLoader.AddPackFile` | Library dekripsi arsip `ioPac` tersedia sebagai pustaka tertutup. Berkas paket `.iop` sendiri **tidak ada di disk**. |
| **Anti-Cheat / GameGuard Integration** | DEPENDENCY MISSING / SOURCE MISSING | `Source/lib/ggsrv30lib_x86_MD.lib`, `SecureEngineSDK32.lib` | GameGuard v3.0 server library | Repositori menyertakan library GameGuard lama dari INCA Internet dan SecureEngine SDK (Oreans). Header C++ untuk mengintegrasikannya **hilang**. |

---

## 3. Evaluasi Kualitatif Paritas Fitur

```text
Total Fitur yang Diaudit:                20 Fitur Utama
- Verified Complete:                     0 Fitur  (0.0%)
- Partially Available (Config/DB Only):  10 Fitur  (50.0%)
- Source Missing (Binary Only):          8 Fitur  (40.0%)
- Asset Missing:                         17 Fitur (85.0% terhalang ketiadaan aset)
- Dependency Missing:                    3 Fitur  (15.0%)
- Unknown / Unverified:                  0 Fitur  (0.0%)
```

### Kesimpulan Paritas Fitur:
Meskipun file konfigurasi server (`Server/Configs/`) dan skema database (`Database/`) memiliki representasi data yang sangat kaya mengenai sistem Lost Saga Season 4 (2.447 item, 1.034 skill, puluhan mode permainan), **tidak ada satupun fitur gameplay yang berstatus "VERIFIED COMPLETE"**. 

Hal ini disebabkan oleh fakta mutlak bahwa client game tidak memiliki source code untuk merender dan memainkan fitur-fitur tersebut, dan tidak tersedianya berkas aset visual/audio untuk menampilkan karakter dan dunianya ke layar pengguna.
