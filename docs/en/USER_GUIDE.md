# RogueByte Forensic Recovery Pro (RFRP) - User Guide
**Developer:** SidoDev-Dz  
**Brand:** RogueByte  
**Version:** 2.4.0-ForensicPro (C++20 & Qt 6)

## 1. Introduction
RogueByte Forensic Recovery Pro is a native digital forensics and incident recovery desktop workstation. It enforces read-only evidence access, SHA-256 verification, and strict chain-of-custody documentation.

## 2. Core Workflows
1. **[01] Case Management:** Create or open a case container.
2. **[02] Evidence Registration:** Ingest raw bit-stream images (.dd, .raw) with cryptographic verification.
3. **[03] RAM Acquisition:** Check provider privileges (WinPmem, LiME) and extract volatile memory safely.
4. **[07] Hex Viewer:** 64-bit address inspection with byte selection and carving navigation.
5. **[09 & 10] File Carving:** Sector-aligned deep carving for JPEG, PNG, PDF, ZIP, SQLite, ELF, and PE.
6. **[11] Hash Validation:** Compare actual hashes with court warrant expectations.
7. **[13] Reporting:** Generate certified reports in HTML, JSON, and PDF.

## 3. Running the Windows CLI
Run `rfrp_cli.exe` from PowerShell or Command Prompt with the required arguments so its output remains visible. When double-clicked, the console may close as soon as the command exits. Running without arguments displays usage instructions.
