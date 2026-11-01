# C++ Linux Systems learning topic

This topic develops the shared technical base for two career directions: industrial/CAE platform engineering and Linux C++ services or middleware. It combines modern C++ ownership, Linux diagnostics, concurrency, networking, and performance in one sequence so the capabilities can converge in system-sized work.

The cross-topic calendar and career checkpoints live in [the shared annual plan](../../learning/cpp-career-plan-2026-2027.md). This topic's [roadmap](learning/roadmap.md) owns only its exercises and exit evidence.

## Start here

1. Review [learning/profile.md](learning/profile.md) and run the M0 baseline without AI assistance.
2. Follow [learning/roadmap.md](learning/roadmap.md) one milestone at a time.
3. Keep focused exercises under `exercises/<lesson>/` and generated output under `out/cpp-linux-systems/<lesson>/`.
4. Append verified practice and explanations to [learning/log.md](learning/log.md).

## Development environment

Use native macOS for lessons whose required behavior, APIs, tools, and checks are equivalent on macOS and Linux. Each exercise identifies its platform before the learner starts. When platform differences affect the lesson, the coach explains the difference and prepares the selected local Colima Linux environment before assigning that work. Unknown equivalence must be checked rather than assumed.

M0 begins with native macOS RAII practice. Linux environment setup is scheduled when the first platform-dependent exercise needs it. Keep macOS and Linux build trees separate, for example `out/cpp-linux-systems/m0/macos/` and `out/cpp-linux-systems/m0/linux/`. Platform-specific success is recorded only for the environment actually tested.

## Scope

- Modern C++: RAII, value and move semantics, smart pointers, exception safety, STL, templates, concepts, library boundaries, and ABI basics.
- Linux: file descriptors, files, processes, signals, pipes, dynamic libraries, GDB, core dumps, and diagnostic tools.
- Concurrency: threads, synchronization, atomics, task queues, thread pools, cancellation, timeouts, and graceful shutdown.
- Networking: TCP stream semantics, framing, partial I/O, non-blocking I/O, epoll, Boost.Asio, backpressure, and failure recovery.
- Performance and quality: repeatable benchmarks, perf, sanitizers, tests, fault injection, and measurement reports.

The long-running flagship project belongs in a separate repository after its scope is approved. This topic holds small, public, reproducible exercises and preparatory prototypes only.

## Verification shape

Each exercise must document exact commands. A typical CMake-based exercise uses:

```sh
cmake -S topics/cpp-linux-systems/exercises/<lesson> -B out/cpp-linux-systems/<lesson> -G Ninja
cmake --build out/cpp-linux-systems/<lesson>
ctest --test-dir out/cpp-linux-systems/<lesson> --output-on-failure
```

Linux-only evidence must name the actual Linux environment. Successful compilation on macOS or Windows is not evidence for Linux-specific behavior such as epoll, core dumps, or perf.
