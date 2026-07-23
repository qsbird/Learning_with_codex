# Learning Workspace

This repository hosts multiple, independent learning topics. Shared conventions live at the repository root; topic-specific instructions live in `topics/<topic>/AGENTS.md`.

## Workspace layout

- `topics/<topic>/`: a self-contained learning topic, including its exercises, learning records, and topic README.
- `learning/`: shared templates and conventions for creating a topic's learning records.
- `.agents/skills/`: reusable, repository-discovered Codex skills. `learning-coach` is topic-neutral; a topic may add a focused skill such as `cmake-coach`.
- `out/`: disposable local build and generated output. Never commit it.

## Adding a topic

1. Create `topics/<topic>/README.md`, `topics/<topic>/learning/`, and the topic's exercise or project directories.
2. Seed its `learning/` files from `learning/_templates/` and tailor the roadmap to official documentation and the learner's goal.
3. Add `topics/<topic>/AGENTS.md` only for rules that do not apply to other topics.
4. Add a topic skill under `.agents/skills/<topic>-coach/` when the topic needs domain-specific workflow, references, or tools. Keep the shared `learning-coach` generic.

## Learning verification

- Keep generated files outside source directories when practical, preferably under `out/<topic>/`.
- Verify a changed exercise with the smallest relevant configure, build, run, or test command before recording it as complete.
- Append evidence and remaining misconceptions to the active topic's `learning/log.md` after each completed lesson.

## End-of-session GitHub sync

At the end of a completed learning session, when tracked learning materials have changed:

1. Inspect `git status` and stage only source, `topics/`, `learning/`, `.agents/skills/`, and relevant repository guidance.
2. Do not stage generated build trees, IDE state, `.DS_Store`, or `.omx/` state.
3. Create one Lore-protocol commit that describes the learning progress and verification.
4. Push `main` to `origin`.

If there are no changes, do not create an empty commit. If the push cannot authenticate or fails, report the exact blocker in the final session update.
