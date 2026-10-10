# Packaging RogueByte Forensic Recovery Pro for Windows x64
$ErrorActionPreference = "Stop"
Write-Host "=== Packaging for Windows x64 ==="

$projectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$buildDir = Join-Path $projectRoot "build\windows-release"
$cliExe = Join-Path $buildDir "rfrp_cli.exe"
$binDir = Join-Path $projectRoot "dist\bin"

if (-not (Test-Path $cliExe)) {
    throw "CLI executable not found: $cliExe. Build the windows-build preset first."
}

New-Item -ItemType Directory -Force -Path $binDir | Out-Null
Copy-Item $cliExe -Destination $binDir

$archive = Join-Path $projectRoot "rfrp_windows_x64.zip"
Compress-Archive -Path (Join-Path $projectRoot "dist\*") -DestinationPath $archive -Force
Write-Host "[+] Package created: $archive"
