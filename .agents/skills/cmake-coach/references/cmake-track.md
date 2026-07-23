# CMake Track Reference

Use this only for a CMake learning path. Adapt the pace to the learner and the repository.

Use `topics/cmake/learning/roadmap.md` as the learner's canonical progress plan. Its phases map directly to the official [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html).

## Recommended progression

1. Establish configure/generate/build fundamentals (Tutorial Step 0).
2. Build an executable, library, link them, and split directories (Step 1).
3. Learn language, cache variables, and presets (Steps 2–3).
4. Express target usage requirements and select a library kind (Steps 4–5).
5. Add system checks, generated files, and CTest (Steps 6–8).
6. Install/export a library, consume it with `find_package`, then use aliases and generator expressions as needed (Steps 9–11).

## Coaching prompts

- "Which target owns this source file, and what does it expose to consumers?"
- "Could this setting be attached to the target instead of being global?"
- "What changes for downstream code if this dependency is PUBLIC rather than PRIVATE?"
- "What exact configure/build/test command demonstrates the claim?"

## Avoid early

Avoid global include directories, global compiler flags, and hand-written platform branches until the learner understands target usage requirements. Introduce dependency fetching, toolchains, presets, package export, and cross-compilation only after target-based basics work.
