# Qt learning topic

This topic teaches modern Qt 6 Widgets and CMake through small, independently buildable exercises. It does not require a production codebase or any fixed local path.

## Choose a learning mode

- **Standalone mode (default):** Work only in `exercises/` and build under `out/qt/`. Use this mode on a new machine or whenever no suitable reference project is available.
- **Project-mapping mode (optional):** Use a local Qt project that you explicitly choose to compare design decisions with the exercises. Record its name, branch or revision, Qt version, and local root path in `learning/profile.md`. Treat it as read-only unless a later exercise explicitly authorizes a scoped change.

Never assume that a particular external project, drive letter, or sibling directory exists. If a reference project is unavailable, continue with the standalone exercise and use Qt's official examples or another project chosen for that session.

## Start here

1. Fill in [learning/profile.md](learning/profile.md) and choose a learning mode.
2. Follow [learning/roadmap.md](learning/roadmap.md); append evidence to [learning/log.md](learning/log.md).
3. Create one focused exercise under `exercises/` and keep generated output under `out/qt/`.

## VS Code and CMake Tools

Open the repository root in VS Code and point CMake Tools at `topics/qt/`. That directory contains a stable aggregate `CMakeLists.txt` exposing every available Qt exercise as a separate target, while each exercise remains independently configurable from the terminal.

Select the active build and launch target in the CMake Tools sidebar. New lesson scaffolding adds its directory to the aggregate entry point, so the VS Code source directory does not change between chapters. Keep the machine-specific Qt Kit path in ignored local VS Code settings rather than committing it to the repository.

## Verification

Use an isolated build tree for each exercise. For a Qt 6 Widgets exercise, the shape is:

```powershell
cmake -S topics/qt/exercises/<lesson> -B out/qt/<lesson> -DCMAKE_PREFIX_PATH="<Qt6-kit>"
cmake --build out/qt/<lesson> --config Debug
```

Replace `<Qt6-kit>` with the Qt 6 Kit selected for this machine. Record the exact Kit, generator, command, and result in the learning log.
