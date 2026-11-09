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

```bash
./build/debug/chip8.exe
```

This opens the emulator window. Close it to exit. The C++ runtime is linked statically, so the executable runs without any extra DLLs.

## Testing

```bash
ctest --preset debug
```

Tests use [Catch2](https://github.com/catchorg/Catch2) and live in `tests/`.

## CLion

1. Open the project folder. CLion detects `CMakePresets.json`.
2. In **Settings → Build, Execution, Deployment → Toolchains**, add a toolchain that uses the llvm-mingw `bin` folder.
3. In **Settings → Build, Execution, Deployment → CMake**, enable the `Debug` and `Release` preset profiles and disable the default `Debug` profile.
4. Choose the `chip8` run configuration to launch the emulator, or `chip8_tests` to run the tests.

## Learning References

- [Tobias Langhoff's guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/): high-level walkthrough
- [Cowgod's technical reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Chip-8 Design Specification](https://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)
- [An Introduction to Chip-8 Emulation using the Rust Programming Language](https://github.com/aquova/chip8-book)
- [Building a CHIP-8 Emulator C++](https://austinmorlan.com/posts/chip8_emulator/)
- [CHIP-8 Variant Opcode Table](https://chip8.gulrak.net)