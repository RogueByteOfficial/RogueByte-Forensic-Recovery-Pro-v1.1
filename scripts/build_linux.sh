#!/usr/bin/env bash
# RogueByte Forensic Recovery Pro - Linux Build Script
# Developer: SidoDev-Dz | Brand: RogueByte
set -euo pipefail

echo "=== Building RogueByte Forensic Recovery Pro (Linux x86-64) ==="
cmake --preset linux-x64-release
cmake --build --preset linux-build
ctest --preset linux-test

echo "[+] Build and CTest validation successful!"
