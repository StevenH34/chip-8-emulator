cmake_minimum_required(VERSION 3.25)
project(chip8 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CHIP8_BUILD_TESTS "Build unit tests" ON)

# Warning flags shared by our own targets (not applied to dependencies)
add_library(chip8_warnings INTERFACE)
if(MSVC)
  target_compile_options(chip8_warnings INTERFACE /W4 /permissive-)
else()
  target_compile_options(chip8_warnings INTERFACE -Wall -Wextra -Wpedantic -Wconversion)
endif()
# Catch2's TEST_CASE uses __COUNTER__, which Clang's -Wpedantic flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(chip8_warnings INTERFACE -Wno-c2y-extensions)
endif()

# Link the C++ runtime (libc++, libunwind) statically so the executables
# don't need DLLs from the MinGW toolchain folder
if(MINGW)
  add_link_options(-static)
endif()

# --- Dependencies -------------------------------------------------------------
include(FetchContent)

# Static SDL3 so there's no SDL3.dll to copy next to the executable
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.16
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SDL3)

# --- App ----------------------------------------------------------------------
add_executable(chip8 src/app/main.cpp
        src/core/chip8.cpp
        src/core/chip8.h
        src/app/display.cpp
        src/app/display.h
        src/app/input.h
        src/app/audio.cpp
        src/app/audio.h
)
target_link_libraries(chip8 PRIVATE chip8_warnings SDL3::SDL3)

# --- Tests --------------------------------------------------------------------
if(CHIP8_BUILD_TESTS)
  FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(Catch2)

  enable_testing()
  add_executable(chip8_tests tests/smoke_tests.cpp)
  target_link_libraries(chip8_tests PRIVATE chip8_warnings Catch2::Catch2WithMain)

  include(Catch)
  catch_discover_tests(chip8_tests)
endif()
