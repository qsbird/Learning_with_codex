# Learning Workspace

This repository hosts multiple, independent learning topics. Shared conventions live at the repository root; topic-specific instructions live in `topics/<topic>/AGENTS.md`.

## Workspace layout

- `topics/<topic>/`: a self-contained learning topic, including its exercises, learning records, and topic README.
- `learning/`: shared templates and conventions for creating a topic's learning records.
- `.agents/skills/`: reusable, repository-discovered Codex skills. `learning-coach` is topic-neutral; a topic may add a focused skill such as `cmake-coach`.
- `out/`: disposable local build and generated output. Never commit it.

## Instruction ownership

- This root file owns repository layout, learning-record conventions, and Git closure authorization.
- `learning-coach` owns topic-neutral teaching, practice, and evidence decisions; it follows this file for record and repository closure.
- `topics/<topic>/AGENTS.md` contains only constraints unique to that topic.
- A topic coach contains only domain-specific references, explanations, and verification choices; it uses `learning-coach` instead of repeating the generic workflow.

## Adding a topic

1. Create `topics/<topic>/README.md`, `topics/<topic>/learning/`, and the topic's exercise or project directories.
2. Seed its `learning/` files from `learning/_templates/` and tailor the roadmap to official documentation and the learner's goal.
3. Add `topics/<topic>/AGENTS.md` only for rules that do not apply to other topics.
4. Add a topic skill under `.agents/skills/<topic>-coach/` when the topic needs domain-specific references, teaching notes, or verification choices. Keep the shared `learning-coach` generic.

## Learning verification

- Keep generated files outside source directories when practical, preferably under `out/<topic>/`.
- Verify a changed exercise with the smallest relevant configure, build, run, or test command before recording it as complete.

## Verified lesson closure

When a lesson meets its stated exit evidence, this repository grants standing authorization to:

1. append the date, outcome, taught knowledge, learner-owned evidence, verification command and result, misconception, learner explanation, and next step to `topics/<topic>/learning/log.md`;
2. update `topics/<topic>/learning/roadmap.md` only when that roadmap's stage exit criterion is met;
3. inspect `git status` and stage only the active lesson's source, learning records, Skills, and relevant guidance;
4. create one scoped commit using `lore: <verified learning outcome>` and push `main` to `origin`.

Do not request this authorization again. Do not create an empty commit or stage generated output, IDE state, `.DS_Store`, or `.omx/` state.

Do not report a completed lesson until the learner evidence, verification, and local learning record are complete. After a successful push, end with exactly:

```text
章节：<lesson-id>
章节状态：已完成
学习日志：已更新 topics/<topic>/learning/log.md
仓库同步：已同步 <commit>
```

`<lesson-id>` identifies the completed lesson, not its enclosing roadmap stage.

If synchronization fails, preserve the local commit and replace only the final line with `仓库同步：待同步——<exact reason>`. Before a later session begins a new lesson, inspect and recover any uncommitted learning record, conflict, or local commit not present at the configured upstream. Never force-push to resolve a lesson-closing conflict.
