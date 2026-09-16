# C++ Linux Systems topic rules

- Keep each exercise self-contained under `exercises/<lesson>/` and generated files under `out/cpp-linux-systems/<lesson>/`.
- Default to C++20, target-based CMake, and CTest; introduce a newer language mode only when the lesson explicitly needs it.
- Use synthetic or public fixtures only. Never copy company code, data formats, screenshots, architecture, or internal measurements.
- Keep unsafe and intentionally broken variants isolated and clearly named; verify them with the relevant sanitizer before repairing them.
- Run ASan/UBSan and TSan in separate build trees unless the active toolchain explicitly supports the requested combination.
- Record the operating system, compiler, build type, test data, and command for benchmarks or platform-specific evidence.
- Treat Linux-only APIs and tools as verified only when run in a named Linux environment; do not substitute a macOS or Windows build result.
- Keep absolute performance numbers secondary to repeatability. Compare changes against the same data, hardware, build type, and command.
- Keep flagship-project implementation in its own repository. This topic may contain bounded compatibility experiments, parsers, queues, protocol labs, and benchmarks that prepare for it.
