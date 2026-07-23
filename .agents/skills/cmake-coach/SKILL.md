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
- Before assigning a CMake command, generator choice, `CMakeLists.txt` declaration, or preset field, teach its minimal syntax and when CMake consumes it. Use the syntax-first sequence in `learning-coach`; do not place unexplained keys or command forms only in the exercise instructions.
- Let the learner own exercise implementation; provide the smallest runnable scaffold and a hint ladder when they need help.
- Configure and build from an isolated directory under `out/cmake/`, never inside an exercise.
- Verify the smallest relevant behavior: configure, build, executable run, or CTest command.
- Record reproducible command evidence and any misconception in `topics/cmake/learning/log.md`; update the roadmap only after its stated exit evidence is met.

## Explain CMake syntax in context

- **Generators and configurations:** Before asking about Ninja or Visual Studio, state whether the generator chooses one configuration at configure time or supports several in one build tree. Show the matching configure and build commands, then ask the learner to predict whether `--config Debug` and `--config Release` can reuse that tree.
- **CMake commands:** For a new command, show its smallest complete call, explain positional arguments and keywords, then trace which target or directory state changes.
- **Presets:** First identify the JSON location (`configurePresets` or `buildPresets`) and the relationship between a configure preset and the build preset that names it. Show one minimal valid object; explain `name`, `inherits`, `binaryDir`, and any new field before asking for an edit.
- **Conditions:** Describe `condition` as an availability filter for a preset, not a mechanism that changes compiler, generator, or cache settings. Explain the condition object's `type`, `lhs`, and `rhs`, including any placeholder such as `${hostSystemName}`, before using it in an exercise.

Read [references/cmake-syntax-teaching.md](references/cmake-syntax-teaching.md) when preparing lessons about generators or presets.

## CMake defaults

- Prefer named targets and target-local usage requirements.
- Defer global include paths, global compiler flags, dependency fetching, package export, and cross-compilation until their prerequisites appear in the roadmap.
- Preserve separate build trees for different options or presets.
