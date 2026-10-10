# RogueByte Forensic Recovery Pro (RFRP)
**Professional Digital Forensics and Incident Recovery Workstation**

- **Developer:** SidoDev-Dz
- **Brand / Organization:** RogueByte
- **Application Type:** Native Digital Forensics Command-Line Tool
- **Primary Language:** C++20 (ISO/IEC 14882:2020)
- **Build System:** CMake (Presets & Ninja)
- **Test Framework:** CTest
- **Primary Platforms:** Windows 10/11 x64 and Linux x86-64
- **Interface & Documentation Languages:** Arabic (RTL) and English (LTR)

---

## 1. Features
- **Strict Evidence Protection:** Source evidence is enforced strictly read-only.
- **Real File Carving:** Sector-aligned signature carving (JPEG, PNG, PDF, ZIP, SQLite, ELF, PE) with header/trailer validation and candidate extraction.
- **Volatile Memory Analysis:** Volatility 3 structured adapter inspecting processes, DLLs, and virtual address descriptors (VAD).
- **64-bit Memory & Binary Hex Viewer:** 64-bit offsets, 16-byte row representation, and binary range export.
- **Cryptographic Hash Validation:** Standard OpenSSL EVP SHA-256 calculation with byte-for-byte baseline comparison.
- **Bilingual Forensic Reporting:** Certified investigation report generation in HTML, JSON, and printable PDF.

---

## 2. Build from Source
### Linux (Ubuntu 22.04 / Debian 12 / Fedora)
```bash
sudo apt-get update
sudo apt-get install -y cmake ninja-build g++ libssl-dev libsqlite3-dev qt6-base-dev
cmake -G Ninja -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

### Windows 10/11 x64 (Visual Studio 2022)
```powershell
cmake --preset windows-x64-release
cmake --build --preset windows-build
ctest --preset windows-test
```

---

## 3. CLI Usage
Run `rfrp_cli.exe` from PowerShell or Command Prompt so its output remains visible. Double-clicking the executable opens a console briefly and closes it when the command finishes. On Windows, for example:
```powershell
cd build\windows-release
.\rfrp_cli.exe --test-suite
```

On Linux:
```bash
./build/rfrp_cli --carve /path/to/evidence.dd --out /path/to/recovered/ --aligned
./build/rfrp_cli --hash /path/to/evidence.dd --expected <SHA256_HEX>
./build/rfrp_cli --test-suite
```

---

## 4. License
MIT License - Copyright (c) 2026 RogueByte / SidoDev-Dz
