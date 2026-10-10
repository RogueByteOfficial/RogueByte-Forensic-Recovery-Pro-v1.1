# RogueByte Forensic Recovery Pro - Windows Build Script
# Developer: SidoDev-Dz | Brand: RogueByte
$ErrorActionPreference = "Stop"

Write-Host "=== Building RogueByte Forensic Recovery Pro (Windows x64) ===" -ForegroundColor Cyan
cmake --preset windows-x64-release
if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed with exit code $LASTEXITCODE." }

cmake --build --preset windows-build
if ($LASTEXITCODE -ne 0) { throw "CMake build failed with exit code $LASTEXITCODE." }

ctest --preset windows-test --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "CTest failed with exit code $LASTEXITCODE." }

$cliExe = Join-Path $PSScriptRoot "..\build\windows-release\rfrp_cli.exe"
if (-not (Test-Path $cliExe)) {
    throw "The CLI executable was not built: $cliExe."
}

Write-Host "[+] Windows CLI built and CTest passed." -ForegroundColor Green
