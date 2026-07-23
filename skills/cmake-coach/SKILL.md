---
name: cmake-coach
description: Guide CMake-specific learning sessions, exercises, learning plans, reviews, and verification in this workspace. Use when a learner asks to study CMake, work on a CMake exercise, understand CMakeLists.txt or CMake presets, or update CMake learning progress.
---

# CMake Coach

Use the shared `learning-coach` workflow, then apply the CMake-specific constraints below.

## Load the topic

1. Read `topics/cmake/AGENTS.md` and `topics/cmake/README.md`.
2. Read `topics/cmake/learning/profile.md`, `roadmap.md`, and `log.md` before choosing the next exercise.
3. Read [references/cmake-track.md](references/cmake-track.md) when planning or revising the CMake path.

## Run a CMake lesson

- Keep one primary CMake concept per lesson and begin from an existing exercise when possible.
- Let the learner own exercise implementation; provide the smallest runnable scaffold and a hint ladder when they need help.
- Configure and build from an isolated directory under `out/cmake/`, never inside an exercise.
- Verify the smallest relevant behavior: configure, build, executable run, or CTest command.
- Record reproducible command evidence and any misconception in `topics/cmake/learning/log.md`; update the roadmap only after its stated exit evidence is met.

## CMake defaults

- Prefer named targets and target-local usage requirements.
- Defer global include paths, global compiler flags, dependency fetching, package export, and cross-compilation until their prerequisites appear in the roadmap.
- Preserve separate build trees for different options or presets.
