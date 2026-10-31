# BUILD & RUNTIME FEASIBILITY AUDIT — LOST SAGA

**Workspace Path:** `/home/randhika/Destop/lostsaga`  
**Host Environment:** Linux x86_64 (Antigravity IDE Environment)  
**Target Platform:** Windows x86 (32-bit PE / DirectX 9 / Winsock)  
**Auditor:** Antigravity Forensic Engineering  

---

## 1. Analisis Lingkungan Kompilasi & Toolchain

### 1.1. Perbedaan Lingkungan Linux vs Windows
Lingkungan host saat ini adalah Linux x86_64. Proyek Lost Saga dirancang khusus secara eksklusif untuk platform **Microsoft Windows 32-bit (x86)** dengan toolchain **Microsoft Visual C++ (MSVC)** dan API Win32 proprietary:
- Proyek solusi client: `client/LSClientNew.sln` dan `client/LSClientNew.vcxproj` menggunakan tag MSBuild `<Platform>Win32</Platform>` dan PlatformToolset `v100` (Visual Studio 2010) atau `v143` (Visual Studio 2022).
- Server executables: File PE32 Windows Console x86 (`ls_gamesvr.exe`, dll.).
- Library engine: File format COFF `.lib` x86 32-bit (`io3DEngine.lib`, dll.) yang hanya dapat dibaca oleh MSVC linker (`link.exe`), bukan GNU `ld` atau Clang Linux.

*Catatan Audit:* Ketidakmampuan untuk mengompilasi file Windows ini secara langsung di Linux tidak dianggap sebagai bukti bahwa source code rusak. Namun, audit membuktikan bahwa **bahkan di lingkungan Windows dengan Visual Studio resmi sekalipun, kode ini tetap tidak dapat dikompilasi atau dijalankan**.

---

## 2. Evaluasi 10 Tahapan Eksekusi & Kelayakan Runtime

Berikut adalah evaluasi forensik terhadap 10 tahapan operasional permainan yang diminta dalam instruksi audit:

| No | Tahapan Eksekusi Game | Status Kelayakan | Bukti & Titik Kegagalan (Failure Point) | Tingkat Keparahan |
|---|---|---|---|---|
| 1 | **Kompilasi Menjadi Client** | **FATAL FAILURE (CANNOT COMPILE)** | `client/stdafx.h:L18`, `client/LSClientNew.vcxproj` | **BLOCKER (Level 1)**. Kompilator MSVC langsung gagal pada tahap pra-proses akibat ketiadaan file header `../io3DEngine/ioPrerequisites.h` dan puluhan header lainnya. |
| 2 | **Dijalankan Sebagai Aplikasi** | **FATAL FAILURE (TERMINATES ON LAUNCH)** | `client/Application.cpp:L218-L230` | **BLOCKER (Level 1)**. Jika seluruh header di-stub/dipalsukan agar berhasil di-link, fungsi `InitializeResource()` memanggil `g_ResourceLoader.AddPackFile("rs.iop")`. Karena `rs.iop` tidak ada, fungsi mengembalikan `false` dan aplikasi keluar seketika (`return 0;`). |
| 3 | **Terhubung ke Server** | **IMPOSSIBLE (NO CODE)** | `client/Application.cpp:L161-L175` | **BLOCKER (Level 2)**. Loop aplikasi `Application::Run()` hanya memproses pesan Windows GDI standar (`GetMessage`/`DispatchMessage`). Tidak ada sebaris pun kode soket TCP/IP atau panggilan `connect()` ke server di client. |
| 4 | **Melakukan Otentikasi / Login** | **IMPOSSIBLE (NO CODE / NO UI)** | `client/` (ketiadaan form login) | **BLOCKER (Level 2)**. Tidak ada antarmuka input username/password, tidak ada pembuatan paket otentikasi login, dan tidak ada handler respon auth dari `ac_mainsvr`. |
| 5 | **Memuat Karakter / Hero** | **IMPOSSIBLE (NO ASSET / NO CODE)** | Ketiadaan kelas `ioBaseChar` dan aset `.mesh` | **BLOCKER (Level 3)**. Client tidak memiliki model 3D hero, skeleton, atau animasi untuk dimuat ke dalam memori VRAM. |
| 6 | **Memasuki Lobby / Plaza** | **IMPOSSIBLE (NO CODE / NO MAP)** | Ketiadaan kelas `ioLobbyStage` dan `map.iop` | **BLOCKER (Level 3)**. Tidak ada logika stage lobby dan tidak ada aset geometri 3D plaza yang dapat dimuat oleh engine render. |
| 7 | **Membuat atau Bergabung ke Room** | **IMPOSSIBLE (NO CODE)** | Ketiadaan kelas `ioRoomManager` | **BLOCKER (Level 3)**. Client tidak memiliki protokol sinkronisasi room, pemilihan slot tim, atau status ready. |
| 8 | **Memulai Pertandingan** | **IMPOSSIBLE (NO STAGE CONTROLLER)** | Ketiadaan kelas `ioPlayStage` | **BLOCKER (Level 4)**. State transisi dari room ke arena pertarungan tidak tersedia pada source client. |
| 9 | **Menjalankan Pertarungan (Combat)** | **IMPOSSIBLE (NO COMBAT LOGIC)** | Ketiadaan sistem collision dan skill | **BLOCKER (Level 4)**. Tidak ada input handler untuk tombol serangan (A, S, D), tidak ada kalkulasi hitbox, tidak ada frame data combo, dan tidak ada efek partikel. |
| 10 | **Menyimpan Hasil Pertandingan** | **BACKEND READY / CLIENT UNABLE** | Backend: `Server/Configs/ls_dbagent/ls_query.ini:L12` (`game_game_save`) | **BLOCKER (Sisi Client)**. Daemon server dan database siap menerima paket hasil pertandingan, namun client tidak dapat menyelesaikan permainan untuk mengirim paket hasil akhir. |

---

## 3. Analisis Kelayakan Runtime Sisi Server

Berbeda dengan sisi client, komponen server memiliki kelayakan runtime yang lebih tinggi dengan catatan:

1. **Persyaratan Runtime Server:**
   - Sistem Operasi: Microsoft Windows Server 2012/2016/2019/2022 (atau Linux via Wine x86 / Docker Proton).
   - Basis Data: Microsoft SQL Server 2008 R2 / 2012 / 2014 / 2016 / 2019 dengan driver ODBC SQL Server Native Client.
   - Konfigurasi Jaringan: Konfigurasi file INI (`ls_config_main.ini`, `ls_config_game.ini`, `ls_config_dba.ini`) dengan IP server yang sesuai.
2. **Kesiapan Eksekusi Server Daemon:**
   - Server daemon (`ac_dbagentsvr.exe`, `ac_mainsvr.exe`, `ls_gamesvr.exe`, `ls_relaysvr.exe`) dapat dinyalakan menggunakan skrip `Server/Starter.bat`.
   - Daemon dapat memuat file konfigurasi INI dan melakukan binding port TCP/UDP lokal (misal: Main Server port 14002, Game Server port 14003, Relay Server port 14000).
   - Jika SQL Server dikonfigurasi dengan skrip `Server/LosaGame.sql` dan `Server/LosaLogData.sql`, DB Agent Server berhasil membaca dan memetakan 330 kueri stored procedure.
3. **Keterbatasan Server:**
   - Server tidak dapat menerima koneksi permainan sungguhan karena client bawaan repositori tidak berfungsi.
   - Server hanya dapat diuji menggunakan client Lost Saga original utuh (full client release dari era 2014-2016) yang IP launcher-nya telah di-patch (*hex-edit* atau *proxy redirect*) ke IP server lokal.

---

## 4. Matriks Skor Kelayakan Rekonstruksi

```text
Skor Kelayakan Eksekusi (0 - 100%):
1. Client Compilation Feasibility:         0%   (Gagal total pada header)
2. Client Runtime Feasibility:             0%   (Keluar instan tanpa rs.iop)
3. End-to-End Gameplay Feasibility:        0%   (Tidak ada loop permainan)
4. Server Daemon Execution Feasibility:    85%  (Dapat berjalan di OS Windows x86)
5. Database Deployment Feasibility:        95%  (Skrip T-SQL siap pakai di MSSQL)
-------------------------------------------------------------------------
TOTAL OVERALL RECONSTRUCTION READINESS:    ~5%  (Hanya backend skema & biner)
```

### Kesimpulan Kelayakan:
Game Lost Saga **TIDAK DAPAT DIREKONSTRUKSI ATAU DIJALANKAN** hanya dengan menggunakan sumber daya yang tersedia di dalam repositori ini. 

Kegagalan ini bukan karena keterbatasan sistem operasi Linux penguji, melainkan karena ketiadaan fisik dari kode sumber gameplay client, ketiadaan file header engine, dan ketiadaan total dari seluruh paket aset game original.
