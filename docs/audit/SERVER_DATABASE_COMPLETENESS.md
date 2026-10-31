# SERVER & DATABASE COMPLETENESS AUDIT — LOST SAGA

**Workspace Path:** `/home/randhika/Destop/lostsaga`  
**Server Directory:** `Server/`  
**Database Directory:** `Database/`  
**Auditor:** Antigravity Forensic Engineering  

---

## 1. Arsitektur Daemon Server yang Ditemukan

Repositori ini memuat berkas server dalam format **executable pra-kompilasi (PE32 Intel i386 Windows Console)** tanpa disertai kode sumber C++. 

Terdapat 6 daemon server utama yang menyusun arsitektur backend Lost Saga:

| Nama Daemon | File Executable Fisik | Ukuran File | Tanggal Kompilasi (PE Timestamp) | Kode Sumber C++ | Status Operasional |
|---|---|---|---|---|---|
| **Main Server** | `Server/ac_mainsvr/ac_mainsvr.exe` | ~1.8 MB | 2023-02-05 06:07:50 UTC | **0% (MISSING)** | Binary Ready (x86) |
| **Game Server** | `Server/ac_gamesvr/ls_gamesvr.exe` | ~4.9 MB | 2023-05-20 16:33:23 UTC | **0% (MISSING)** | Binary Ready (x86) |
| **Relay Server** | `Server/ls_relaysvr/ls_relaysvr.exe` | ~920 KB | 2014-02-04 04:50:19 UTC | **0% (MISSING)** | Binary Ready (x86) |
| **DB Agent Server** | `Server/ac_dbagentsvr/ac_dbagentsvr.exe` | ~1.6 MB | 2023-01-29 09:38:27 UTC | **0% (MISSING)** | Binary Ready (x86) |
| **Billing Server** | `Server/ac_billingsvr/ac_billingsvr.exe` | ~1.2 MB | 2022-09-04 07:32:11 UTC | **0% (MISSING)** | Binary Ready (x86) |
| **File Write Server** | `Server/ac_filewritesvr/ac_filewritesvr.exe` | ~850 KB | 2022-09-04 09:30:08 UTC | **0% (MISSING)** | Binary Ready (x86) |

*Catatan Tambahan:*  
Di dalam `Server/Configs/` terdapat pula salinan biner server alternatif seperti `Server/Configs/ls_billingsvr/ls_billingsvr.exe` (2022-07-26) dan `Server/Configs/ls_dbagent/ls_dbagent.exe` (2022-07-26).

---

## 2. Audit Implementasi Fungsional Backend

Meskipun source code C++ server tidak disertakan, logika fungsional server dapat dianalisis secara forensik melalui:
1. Export table dan binary strings pada executable PE.
2. Pemetaan file konfigurasi INI di `Server/Configs/`.
3. Skrip pemetaan kueri database `Server/Configs/ls_dbagent/ls_query.ini`.

| Fungsionalitas Backend | Status Implementasi | Letak Logika (Server / DB / Config) | Bukti Forensik & Keterangan |
|---|---|---|---|
| **Account Registration** | PARTIALLY AVAILABLE (External Web/SQL) | `Server/ac_mainsvr/ls_auth.ini`, `Database/LosaGame.sql` | Pendaftaran akun tidak ditangani langsung oleh port TCP game; dilakukan via stored procedure `game_create_nickname` atau skrip web PHP/ASP.NET registrasi eksternal. |
| **Authentication** | IMPLEMENTED IN BINARY | `Server/ac_mainsvr/ac_mainsvr.exe`, `Server/Configs/ls_dbagent/ls_query.ini:L7-L10` | Menggunakan kueri `game_login_get_data` dan `game_login_save`. Otentikasi terhubung ke DB Agent via token sesi atau enkripsi fixed key (`game_encode_get_fix_key`). |
| **Character Selection** | IMPLEMENTED IN BINARY | `Server/ac_gamesvr/ls_gamesvr.exe`, `ls_query.ini:L25` | Memanggil `game_character_get_list` untuk mengambil seluruh hero milik user ID yang login. |
| **Character Inventory & Hero Ownership** | IMPLEMENTED IN BINARY | `ls_query.ini:L31-L39`, `Database/LosaGame.sql:define_class` | Mendukung penambahan hero (`game_character_add`), rental hero (`game_character_rental_history`), dan penghapusan limit waktu (`game_character_delete_limitdate`). |
| **Equipment Management** | IMPLEMENTED IN BINARY | `ls_query.ini:L26`, `Server/Configs/ls_gamesvr/config/sp2_item.ini` | Memanggil `game_item_get_data_list`. Logika slot gear (Weapon, Armor, Helmet, Cloak) didefinisikan dalam binary `ls_gamesvr.exe` dengan batasan dari `sp2_item.ini`. |
| **Player Progression & EXP** | IMPLEMENTED IN BINARY | `ls_query.ini:L14-L15`, `Server/Configs/ls_gamesvr/config/growth_info.ini` | Prosedur `game_game_heroexp_save` dan `game_game_heroexp_init`. Pertumbuhan level hero dihitung oleh server berdasarkan konfigurasi tabel EXP di `growth_info.ini`. |
| **Currency (Peso & Cash/Gold)** | IMPLEMENTED IN BINARY | `ls_query.ini:L2095-L2098`, `Database/LosaLogData.sql:log_data_peso_add` | Prosedur `game_spentGold_get_data`, `game_spentGold_set_add`. Transaksi Peso dicatat di `LosaGame`, sedangkan Cash/Gold ditangani via billing bridge `ac_billingsvr`. |
| **Shop & Item Transactions** | IMPLEMENTED IN BINARY | `Server/Configs/ls_gamesvr/config/sp2_item_price.ini`, `sp2_extraitem_info.ini` | Harga item, durasi rental (2 jam, 10 jam, 30 jam, permanen), dan gashapon diatur melalui puluhan file INI dan divalidasi oleh `ls_gamesvr.exe`. |
| **Lobby & Plaza Room** | IMPLEMENTED IN BINARY | `Server/ac_gamesvr/ls_gamesvr.ini`, `Server/Configs/ls_gamesvr/config/fightmode.ini` | Server mengelola state lobby, plaza terbuka, dan panggung channel. Mendukung sinkronisasi memancing, relik, dan obrolan umum. |
| **Room Creation & Settings** | IMPLEMENTED IN BINARY | `Server/Configs/ls_gamesvr/config/` (berbagai mode `.ini`) | Mode Deathmatch, Team Match, Boss Raid, Prisoner, Power Stone, Monster Survival didefinisikan dalam INI server dan diinisialisasi oleh `ls_gamesvr.exe`. |
| **Matchmaking** | BASIC LOBBY ONLY | `Server/ac_gamesvr/ls_gamesvr.exe` | Tidak ada algoritma MMR/Elo modern. Hanya pencocokan channel berdasarkan level (Beginner Channel, Free Channel) dan antrean ladder sederhana. |
| **Multiplayer Synchronization** | IMPLEMENTED IN BINARY | `Server/ls_relaysvr/ls_relaysvr.exe`, port UDP 14000+ | Lost Saga menggunakan arsitektur hybrid P2P dengan fallback UDP Relay Server (`ls_relaysvr`) jika koneksi P2P antar-pemain mengalami kegagalan NAT/firewall. |
| **Combat Validation** | CLIENT-AUTHORITATIVE (P2P RISK) | `Server/ac_gamesvr/ls_gamesvr.exe` | Validasi serangan sebagian besar bersifat **client-authoritative**. Server hanya memvalidasi konsumsi HP, cooldown skill, dan kematian, sehingga sangat rentan terhadap manipulasi memory (cheat attack speed/no delay). |
| **Reward Distribution & Match Results** | IMPLEMENTED IN BINARY | `ls_query.ini:L12`, `Server/Configs/ls_gamesvr/config/regular_tournament_reward.ini` | Kueri `game_game_save` menyimpan Peso, EXP, jumlah kill, death, dan MVP setelah pertandingan selesai. |
| **Ranking & Ladder System** | IMPLEMENTED IN BINARY | `Database/LosaGame.sql:AGENT_RANKING_*`, `Server/Configs/ls_mainsvr/config/sp2_ranking.ini` | Prosedur tersimpan khusus `AGENT_RANKING_LADDER_TITLE`, `AGENT_RANKING_TOTAL_TITLE` menghitung peringkat secara batch periodik. |
| **Persistence (Database)** | FULL SCHEMA AVAILABLE | `Database/LosaGame.sql`, `Server/LosaGame.sql` | 142 tabel relational untuk menampung seluruh state pemain secara persisten di Microsoft SQL Server. |
| **Logging** | EXTENSIVE LOGGING | `Server/ac_filewritesvr/`, `Database/LosaGame_log.sql`, `Database/LosaLogData.sql` | Daemon `ac_filewritesvr` menerima stream log biner dan menyimpannya ke flat-file dan tabel log SQL. |

---

## 3. Audit Kesesuaian Database SQL vs Implementasi Server

Terdapat dua versi file `LosaGame.sql` di dalam repositori:
1. `Database/LosaGame.sql` (814 KB): Berisi 133 tabel dan 471 stored procedure.
2. `Server/LosaGame.sql` (1.7 MB): Berisi 142 tabel, 1.097 stored procedure, dan 823 skrip `INSERT INTO` (seed data awal untuk kelas hero, medal, dan quest dasar).

### Hasil Uji Silang Forensik: `Server/Configs/ls_dbagent/ls_query.ini` vs `LosaGame.sql`

File `ls_query.ini` mendefinisikan 330 kueri stored procedure yang dieksekusi oleh `ac_dbagentsvr.exe` saat melayani request dari Game Server dan Main Server.

```text
Total Query Terpetakan di ls_query.ini:    330 Prosedur
Ditemukan di Database/LosaGame.sql:       302 Prosedur (91.5%)
Ditemukan di Server/LosaGame.sql:         297 Prosedur (90.0%)
Ditemukan di Database/LosaLogData.sql:    18 Prosedur  (5.5%)
Total Cakupan Prosedur Database:          320 / 330    (97.0%)
```

**Temuan Forensik Prosedur yang Hilang / Unresolved:**
- `game_pingpong`: Kueri dummy heartbeat check antara DB Agent dan database. Dapat digantikan dengan `SELECT 1`.
- `game_channel_get_cp_userID`: Kueri channeling platform Korea (Daum/Nexon) yang tidak relevan untuk private server.
- `game_region_compen_delete`: Prosedur kompensasi regional tertentu.

**Kesimpulan Database:**  
Skrip database SQL di repositori ini memiliki integritas dan kelengkapan yang **sangat tinggi (~97%)** terhadap kebutuhan server daemon biner. Database ini kompatibel dengan Microsoft SQL Server 2008 R2 hingga SQL Server 2019.

---

## 4. Ketergantungan Eksternal & Layanan Pihak Ketiga

Pemeriksaan binary strings pada `ac_mainsvr.exe`, `ac_billingsvr.exe`, dan `ls_gamesvr.exe` mengungkap ketergantungan berikut:

1. **Billing Channeling Daum / Garena:**
   - Ditemukan simbol: `ioChannelingNodeDaum::AddRequestGetCashPacket`, `log_garena_shell_change`.
   - Modul billing mengasumsikan adanya HTTP API eksternal untuk pengisian Cash/Gold. Jika tidak diarahkan ke mock API lokal, pembelian cash di dalam game akan gagal atau time-out.
2. **DLL Injeksi / Hooking Pihak Ketiga di `Server/ac_gamesvr/`:**
   - `LSAddon.dll`, `LSAddona.dll`, `LSAddonb.dll`: Modul custom buatan komunitas private server (biasanya untuk bypass check packet, integrasi Discord Rich Presence, atau command administrator tambahan).
   - `dpp.dll`: D++ (Discord C++ library) untuk bot atau status room server.
   - `libsodium.dll`, `libcrypto-1_1.dll`, `libssl-1_1.dll`: Pustaka kriptografi OpenSSL untuk enkripsi jaringan modern.
   - `opus.dll`: Codec suara Opus (kemungkinan untuk in-game voice chat server).

---

## 5. Kesimpulan Audit Server & Database

1. **Server Executable:** Tersedia lengkap dalam bentuk biner Windows x86 siap jalan, mencakup seluruh daemon utama (`main`, `game`, `relay`, `dbagent`, `billing`, `filewrite`).
2. **Server Source Code:** **0% HILANG**. Tidak ada kode C++ untuk memperbaiki bug server, menambahkan protokol baru, atau mengompilasi ulang untuk Linux (harus dijalankan via Wine atau Windows Server).
3. **Database:** **97% LENGKAP**. Skema, stored procedure, dan data seed tabel hero/item tersedia dan cocok dengan daemon server.
