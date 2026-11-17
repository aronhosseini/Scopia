param(
    [string]$Configuration = "Release",
    [string]$JucePath = "..\JUCE\modules"
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path "build")) { New-Item -ItemType Directory -Path "build" | Out-Null }
Push-Location build
cmake -A x64 -DJUCE_MODULES_PATH="$JucePath" ..
cmake --build . --config $Configuration
Pop-Location

Write-Host "Build complete: build\$Configuration"