# LICENSE & PROVENANCE AUDIT — LOST SAGA REPOSITORY

**Workspace Path:** `/home/randhika/Destop/lostsaga`  
**Repository URL:** `https://github.com/Xalorra/lsopensource` (Forked from `crayzero0/lsopensource`)  
**Auditor:** Antigravity Forensic Engineering  
**Scope:** Legal Provenance, Copyright Ownership, Intellectual Property (IP), License Validity, and Commercial Risks.

---

## 1. Analisis Lisensi Repositori

Di root direktori repositori terdapat file `LICENSE` yang menyatakan lisensi **MIT License**:

```text
MIT License

Copyright (c) 2024 crayzero

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

### Evaluasi Yuridis Validitas Lisensi:
1. **Ketidakabsahan Lisensi Pihak Ketiga (Null and Void):**
   Lisensi MIT ini **TIDAK MEMILIKI KEKUATAN HUKUM** terhadap binary, library, dan skema database Lost Saga yang ada di dalam repositori. 
   Seseorang atau pembuat repositori (`crayzero`) hanya berhak memberikan lisensi atas kode yang ia ciptakan sendiri dari nol (misalnya 356 baris kode launcher di `client/Application.cpp`).
2. **Karya Turunan Tanpa Izin:**
   Seluruh binary executable di `Server/`, library biner di `Source/lib/`, file konfigurasi INI di `Server/Configs/`, dan skema database di `Database/` adalah hak kekayaan intelektual (IP) milik pemilik asli Lost Saga. Menambahkan file teks lisensi MIT ke dalam arsip file curian atau bocoran (*leaked files*) tidak mengubah status hak cipta aslinya.

---

## 2. Pelacakan Provenance & Asal-Usul Sumber Daya

Berdasarkan metadata biner, jejak debug symbol (PDB), teks disclaimers, dan file konfigurasi, asal-usul setiap komponen dapat dipetakan secara forensik:

| Komponen Repositori | Pemilik Asli / Asal Usul (Provenance) | Status Legalitas | Bukti Forensik Provenance |
|---|---|---|---|
| **Engine Core (`io3DEngine.lib/dll`)** | **IO Entertainment / Wemade / Valofe** | PROPRIETARY CLOSED-SOURCE (Leaked) | `Source/lib/lib_Shipping/io3DEngine.pdb` memuat path `d:\svn\foreign\v20160427\src\io3dengine\` |
| **Server Daemons (`ls_gamesvr.exe`, dll.)** | **IO Entertainment / Valofe** + Komunitas Private Server | PROPRIETARY EXECUTABLE (Leaked & Modded) | String di `ls_gamesvr.exe` memuat nama Daum channeling, SP2 Packet, dan PDB path `d:\work\trunk\` |
| **Relay Server (`ls_relaysvr.exe`)** | **IO Entertainment** | PROPRIETARY EXECUTABLE (Leaked 2014) | PE timestamp tertanggal `2014-02-04 04:50:19 UTC` |
| **Database Schemas (`LosaGame.sql`)** | **IO Entertainment** | CONFIDENTIAL DATABASE SCHEMA (Leaked) | Memuat ratusan stored procedure resmi (`USP_GET_FRIEND_LIST`, `game_character_*`, `define_class`) |
| **Server Configurations (`sp2_*.ini`)** | **IO Entertainment / Garena SEA** | CONFIDENTIAL GAME DATA (Leaked) | Item 2447: "2014 Garena Football T-Shirt", file `sp2_garena_shell_change` |
| **Anti-Cheat SDK (`ggsrv30lib_x86_MD.lib`)** | **AhnLab / INCA Internet Co., Ltd.** | PROPRIETARY THIRD-PARTY SDK (Commercial) | GameGuard v3.0 server library |
| **Proteksi Biner (`SecureEngineSDK32.lib`)** | **Oreans Technologies** | COMMERCIAL SECURITY SDK (Themida / VMProtect) | SDK komersial pelindung anti-reverse engineering |
| **Library Enkripsi (`NMCrypt.lib`)** | **Nexon Co., Ltd. / Netmarble** | PROPRIETARY AUTHENTICATION SDK | Library enkripsi login portal Nexon/Netmarble Korea |
| **Komponen Hooking (`LSAddon*.dll`)** | Modder Komunitas Private Server (Unknown) | REVERSE ENGINEERED / HOOK DLL | Injeksi biner tanpa dokumentasi atau lisensi terbuka |
| **Client Code (`client/Application.cpp`)** | Modder Komunitas (crayzero / private dev) | ORIGINAL CODE (356 baris) | Satu-satunya komponen yang secara sah dapat dicakup oleh lisensi MIT |

---

## 3. Klaim Kepemilikan Intelektual (Intellectual Property - IP)

Game **Lost Saga** adalah merek dagang terdaftar dan karya berhak cipta yang memiliki rantai kepemilikan sejarah:
1. **IO Entertainment Co., Ltd.** (Pengembang asli sejak 2008).
2. Diakuisisi oleh **Wemade Entertainment Co., Ltd.** (sekarang Wemade Co., Ltd.) pada tahun 2012.
3. Hak operasional dan kepemilikan global saat ini dipegang oleh **Valofe Global Ltd.** (termasuk server resmi Lost Saga Origin dan Lost Saga Global).

### Hak Penggunaan:
- **Hak Cipta Kode Biner & Engine:** Tidak pernah dialihkan ke publik (*public domain*) atau dirilis di bawah lisensi Open Source (GPL, MIT, Apache).
- **Aset Visual & Merek Dagang:** Nama "Lost Saga", logo permainan, desain visual karakter, model senjata, dan efek visual sepenuhnya berada di bawah hak cipta Valofe / IO Entertainment.
- **Pengecualian Pembelajaran (Educational Disclaimer):**
  Disclaimer pada `Server/README.md` ("Proyek ini dibuat untuk pembelajaran... Dilarang keras diperjualbelikan") **TIDAK MEMILIKI NILAI PERLINDUNGAN HUKUM** terhadap gugatan pelanggaran hak cipta komersial.

---

## 4. Analisis Risiko Hukum & Kepatuhan (Compliance)

Jika organisasi atau pengembang berniat menggunakan repositori ini untuk tujuan apa pun selain analisis forensik statis internal yang terisolasi, risiko hukum yang dihadapi mencakup:

### 4.1. Pelanggaran Hak Cipta Komersial
- **DMCA (Digital Millennium Copyright Act) & WIPO Copyright Treaty:** Repositori GitHub publik yang menampung file biner bocoran atau skema database proprietary rentan terhadap *DMCA Takedown Notice* sewaktu-waktu dari pemegang hak cipta resmi (Valofe).
- **Hukum Hak Cipta Indonesia (UU No. 28 Tahun 2014):** Penggandaan, distribusi, dan pemanfaatan perangkat lunak tanpa izin pencipta untuk tujuan komersial dapat dikenai sanksi pidana dan perdata (Pasal 113).

### 4.2. Risiko Keamanan Siber (Security & Malware Vulnerability)
- File biner server di `Server/` (`ac_mainsvr.exe`, dll.) dan DLL di `Source/lib/` dikompilasi oleh pihak ketiga yang tidak dikenal (*untrusted private server developers*).
- Terdapat indikasi modifikasi biner (hooking DLL, memory patcher).
- Menjalankan file biner ini di jaringan produksi atau lingkungan tanpa sandbox dapat membuka celah *backdoor*, *remote code execution*, atau infeksi trojan.

---

## 5. Rekomendasi & Arahan Tata Kelola (Governance Direction)

1. **LARANGAN KERAS PENGGUNAAN BINER DALAM PRODUK BARU:**  
   Tidak ada satu pun file `.exe`, `.dll`, `.lib`, atau skema database mentah dari repositori ini yang boleh disertakan, di-link, atau didistribusikan dalam proyek game komersial tim.
2. **METODOLOGI CLEAN-ROOM RE-ENGINEERING:**  
   Jika tim ingin mengembangkan game multiplayer brawler original yang terinspirasi oleh mekanika Lost Saga (gameplay *hero switching*, *gear drop*, pertarungan arena platformer), tim wajib menggunakan pendekatan **Clean-Room Design**:
   - Dokumentasikan spesifikasi mekanika permainan murni secara fungsional (aturan game loop, timing, input).
   - Implementasikan seluruh logika permainan dari nol menggunakan engine modern (seperti Unreal Engine, Godot, atau Unity).
   - Seluruh model 3D, animasi, efek suara, tekstur, dan UI harus dibuat 100% original oleh tim artis 3D sendiri.
   - Mengembangkan arsitektur backend server independen modern (misalnya Go, Rust, C# / .NET) dengan validasi server-authoritative.
3. **ISOLASI ARSIP:**  
   Simpan repositori ini hanya sebagai bahan studi arsitektural dan referensi mekanika dalam lingkungan pengembangan tertutup yang tidak terhubung ke produksi.
