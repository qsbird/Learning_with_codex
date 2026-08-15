# Qt topic rules

- Default to standalone exercises under `exercises/`; do not require an external project or a fixed local path.
- Keep generated output under `out/qt/`, outside the exercise source tree.
- Keep every exercise independently configurable, and also maintain `topics/qt/CMakeLists.txt` as the stable aggregate entry point for IDEs.
- When scaffolding a new exercise, give its CMake targets unique names, add the lesson directory to `QT_LEARNING_EXERCISES`, and verify that its target configures and builds through the aggregate entry point.
- Enter project-mapping mode only when the learner explicitly supplies a local reference project. Record its identity and environment in `learning/profile.md`.
- Treat a reference project as read-only unless a lesson explicitly authorizes a small, scoped change. Do not include it in this repository or commit its files here.
