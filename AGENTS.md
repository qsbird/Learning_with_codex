# CMake Learning Workspace

## Learning verification

- Keep CMake build outputs outside source directories when possible.
- Verify a changed exercise with the smallest relevant configure, build, and run/test command before recording it as complete.
- Append evidence and remaining misconceptions to `learning/log.md` after each completed lesson.

## End-of-session GitHub sync

At the end of every completed learning session, when tracked learning materials have changed:

1. Inspect `git status` and stage only source, `learning/`, `skills/`, and relevant repository guidance.
2. Do not stage generated CMake trees, IDE state, `.DS_Store`, or `.omx/` state.
3. Create one Lore-protocol commit that describes the learning progress and verification.
4. Push `main` to `origin`.

If there are no changes, do not create an empty commit. If the push cannot authenticate or fails, report the exact blocker in the final session update.
