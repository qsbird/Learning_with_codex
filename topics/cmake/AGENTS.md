# CMake topic rules

These rules refine the repository-level learning workspace guidance for `topics/cmake/`.

- Keep each exercise self-contained under `exercises/<lesson>/`.
- Build outside the exercise source tree, under `out/cmake/<lesson>/` when practical.
- Prefer target-based CMake commands and target-local usage requirements over global include paths or compiler flags.
