# p0-hello runtime DLL design

## Goal

Make the CLion Debug build of `hello.exe` runnable directly on Windows while
keeping `greeting` as a shared library.

## Root cause

`hello.exe` is emitted to `cmake-build-debug/app`, while the project runtime
DLL is emitted to `cmake-build-debug/src/libgreeting.dll`. Windows does not
search sibling directories for dependent DLLs. In addition, MinGW runtime DLLs
must be discoverable through the IDE/toolchain environment.

## Design

Add a target-level post-build command in `app/CMakeLists.txt`. It copies
`$<TARGET_FILE:greeting>` to `$<TARGET_FILE_DIR:hello>`. These generator
expressions resolve per build tree and configuration, so the rule does not
hard-code `cmake-build-debug`, preset output paths, or a particular generator.

The MinGW toolchain `bin` directory remains an IDE/user environment concern;
it is not copied by the project build. Future install/package work can collect
the complete runtime dependency set for redistribution.

## Verification

1. Configure and build the CLion Debug build tree.
2. Confirm `app/libgreeting.dll` exists beside `app/hello.exe`.
3. Run `app/hello.exe` with the MinGW toolchain directory on `PATH`, but without
   adding the sibling `src` directory.
4. Confirm the program exits successfully. The pre-change command fails with
   `0xC0000135`, demonstrating the regression is covered.
