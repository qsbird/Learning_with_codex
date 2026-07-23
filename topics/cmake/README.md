# CMake learning topic

This topic follows the official CMake Tutorial while building small, target-based C++ projects. Its current progress and evidence live in [learning/roadmap.md](learning/roadmap.md) and [learning/log.md](learning/log.md).

## Start here

- Use `$cmake-coach` for a CMake-specific guided session.
- Use the generic `$learning-coach` when the session spans multiple topics or needs only the shared learning workflow.
- Work on one exercise at a time under `exercises/`.

## Verification

Keep generated trees under the ignored workspace output directory. For the current hello exercise:

```powershell
cmake -S topics/cmake/exercises/p0-hello -B out/cmake/p0-hello
cmake --build out/cmake/p0-hello
& .\out\cmake\p0-hello\app\hello.exe
```

Use a different `out/cmake/<exercise>` directory for each experiment or configuration. Record the exact command and result in this topic's learning log.
