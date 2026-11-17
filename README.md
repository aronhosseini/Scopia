# Scopia VST3

Scopia is a lightweight audio oscilloscope plugin (VST3 + Standalone) for Windows and macOS.

Developed by [Aron H](https://www.instagram.com/aronh.official/)

## Features
- Real-time waveform display
- Pass-through audio (no coloration)
- Clean, minimal UI

## Building
### Prerequisites
- JUCE 7.0.7+
- CMake 3.22+

### Configure & build (Windows)
```powershell
git submodule add https://github.com/juce-framework/JUCE.git JUCE
mkdir build
cd build
cmake -A x64 -DJUCE_MODULES_PATH=../JUCE/modules ..
cmake --build . --config Release
```

## Installer
Pre-built Windows installer is produced by the GitHub Actions workflow (see `.github/workflows/ci.yml`).

## License
MIT License.