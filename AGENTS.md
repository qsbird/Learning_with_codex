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

## Verified lesson closure

When a lesson meets its stated exit evidence, this repository grants standing authorization to:

1. append the outcome, evidence, misconception, and next step to the active topic's `learning/log.md`;
2. update `learning/roadmap.md` only when a stage exit criterion is met;
3. inspect `git status` and stage only the active lesson's source, learning records, Skills, and relevant guidance;
4. create one Lore-protocol commit and push `main` to `origin`.

Do not request this authorization again. Do not create an empty commit or stage generated output, IDE state, `.DS_Store`, or `.omx/` state.

If synchronization fails, preserve the local commit and report `仓库同步：待同步——<exact reason>`. Before a later session begins a new lesson, inspect and recover any uncommitted learning record, conflict, or local commit not present at the configured upstream. Never force-push to resolve a lesson-closing conflict.
