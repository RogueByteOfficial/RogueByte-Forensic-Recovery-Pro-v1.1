#!/usr/bin/env bash
set -euo pipefail
echo "=== Packaging RogueByte Forensic Recovery Pro for Linux x86-64 ==="
mkdir -p dist/bin dist/docs
cp build/rfrp_cli dist/bin/
cp README.md LICENSE dist/
tar -czvf rfrp_linux_x86_64.tar.gz dist/
echo "[+] Package created: rfrp_linux_x86_64.tar.gz"
