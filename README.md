# chip-8-emulator
CHIP-8 Emulator in C++

## Requirements

- CMake 3.25 or newer
- Ninja
- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) Clang with C++23 support. Its `bin` folder must be on your `PATH`, because the presets look for `x86_64-w64-mingw32-clang` and `x86_64-w64-mingw32-clang++`.

SDL3 and Catch2 are downloaded and built automatically on the first configure, so you don't need to install them. The first configure takes a minute or two.

## Building

```bash
cmake --preset debug
cmake --build --preset debug
```

Use the `release` preset instead of `debug` for an optimized build. Output goes to `build/debug/` or `build/release/`.

If you change compilers or see a "compiler changed" error, reconfigure from scratch with `cmake --preset debug --fresh`.

## Running

Pass the path to a ROM file as the first argument:

```bash
./build/debug/chip8.exe roms/1-chip8-logo.ch8
```

This opens the emulator window. Close it to exit. Relative paths are resolved from the directory you run the command in. The C++ runtime is linked statically, so the executable runs without any extra DLLs.

`roms/` contains `1-chip8-logo.ch8`, the CHIP-8 splash screen from [Timendus' chip8-test-suite](https://github.com/Timendus/chip8-test-suite). It is a quick check that the emulator boots and draws.

### Controls

The CHIP-8 keypad is mapped to the left side of the keyboard:

```
Keypad      Keyboard
1 2 3 C     1 2 3 4
4 5 6 D     Q W E R
7 8 9 E     A S D F
A 0 B F     Z X C V
```

## Testing

```bash
ctest --preset debug
```

Tests use [Catch2](https://github.com/catchorg/Catch2) and live in `tests/`.

## CLion

1. Open the project folder. CLion detects `CMakePresets.json`.
2. In **Settings → Build, Execution, Deployment → Toolchains**, add a toolchain that uses the llvm-mingw `bin` folder.
3. In **Settings → Build, Execution, Deployment → CMake**, enable the `Debug` and `Release` preset profiles and disable the default `Debug` profile.
4. Choose the `chip8` run configuration to launch the emulator, or `chip8_tests` to run the tests. Under **Run → Edit Configurations → chip8**, set **Program arguments** to the ROM path. Use an absolute path, because CLion runs the program from the build directory.
