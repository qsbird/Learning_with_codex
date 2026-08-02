# Learning Closure Hooks Design

## Purpose

Make every verified learning chapter end with a readable Markdown learning record and an explicit GitHub synchronization result. Keep teaching and progress records natural-language-first; use Codex Hooks only as lifecycle guardrails.

The design addresses two observed failures:

1. exercise changes can be committed before the corresponding learning log is updated;
2. a learning turn can end without attempting or reporting repository synchronization.

## Design principles

- `topics/<topic>/learning/log.md` remains the only lesson history and source of learning evidence.
- `roadmap.md` remains the only stage-progress overview.
- Git history and the configured upstream are the synchronization state; do not add a state database or `needs-sync` file.
- Skills make teaching judgments. Hooks check mechanically observable closure facts.
- A network, authentication, or merge failure may end the current task only after it is reported as pending. The next Codex session must surface and retry the pending synchronization before starting a new chapter.
- This change adds no CI workflow and no standalone PowerShell, batch, Python, or Node script.

## Scope

### In scope

- Add project-local Codex `Stop` and `SessionStart` hooks in `.codex/hooks.json`.
- Simplify `learning-coach` and `cmake-coach` without weakening the teaching-first behavior.
- Resolve the conflict between per-action consent in `learning-coach` and repository-authorized lesson synchronization.
- Define a stable natural-language completion contract for Hook recognition.
- Ignore Qt Creator local state.

### Out of scope

- GitHub Actions or other CI enforcement.
- Git hooks installed under `.git/hooks`.
- Automatic generation of learning-log prose.
- Machine-readable lesson status files or auxiliary logs.
- Guaranteeing GitHub availability or covering commits made outside a trusted Codex session.

## Responsibility boundaries

### Repository guidance

The root `AGENTS.md` owns durable repository policy:

- completing a verified lesson carries standing authorization to update that topic's Markdown learning records, create the scoped learning commit, and push `main` to `origin`;
- Codex does not ask for the same authorization again;
- generated output and IDE state remain excluded;
- a failed push is reported exactly and retried before the next lesson.

Topic `AGENTS.md` files contain only topic-specific filesystem, build, verification, and reference-project constraints. They do not repeat the general lesson-closing workflow.

### `learning-coach`

`learning-coach` owns the complete topic-neutral teaching workflow:

1. load the active topic's README, profile, roadmap, and log;
2. treat unrecorded syntax, APIs, functions, and concepts as unfamiliar;
3. teach unfamiliar material with a minimal valid form and a short understanding check before practice;
4. run one-primary-concept practice with observable verification and a graduated hint ladder;
5. mark a lesson complete only after independent evidence and an explanation or small transfer;
6. append the natural-language learning log, update the roadmap only when stage exit evidence is met, commit scoped changes, attempt the push, and report the closure contract.

The current long-form repetitions about difficulty control, practice shape, syntax teaching, and review are consolidated into these contracts. The target size is approximately 900-1100 words; the unfamiliar-knowledge gate and syntax-before-practice requirements remain explicit.

The current rule requiring new explicit consent before every log edit, commit, or push is removed for this repository because root guidance provides standing authorization. Material environment changes, dependency installation, credentials, and changes outside the learning workspace still require confirmation.

### `cmake-coach`

`cmake-coach` becomes a thin domain adapter and explicitly requires `learning-coach` rather than paraphrasing it.

It retains only:

- CMake topic discovery and record locations;
- conditional routing to `references/cmake-track.md` for planning;
- conditional routing to `references/cmake-syntax-teaching.md` for generators, configurations, and presets;
- the requirement to use the smallest relevant configure, build, run, or CTest evidence.

General teaching loops, syntax-first procedure, learner ownership, hint levels, logging, roadmap updates, and publishing are inherited from `learning-coach` and removed from `cmake-coach`. Target-based defaults and `out/cmake/` layout remain in `topics/cmake/AGENTS.md`; detailed generator and preset explanations remain in the existing reference.

The target size is approximately 150-220 words.

## Natural-language completion contract

Normal explanations, questions, and incomplete exercises do not emit a completion block. Once exit evidence is met and closure work has been performed, the final response uses this exact readable shape:

```text
章节：P5.1
章节状态：已完成
学习日志：已更新 topics/cmake/learning/log.md
仓库同步：已同步 <commit>
```

When a push was attempted but failed because of an external condition:

```text
章节：P5.1
章节状态：已完成
学习日志：已更新 topics/cmake/learning/log.md
仓库同步：待同步——<exact error or blocker>
```

The block is a user-facing summary, not a second log. The corresponding Markdown log entry contains the durable learning evidence, misconception, and next step.

Codex must not announce that it is moving to the next chapter while the previous chapter satisfies its exit criteria but lacks this closure. If a lesson remains in progress, it says so normally and does not create a placeholder log entry.

## Hook architecture

Codex discovers `.codex/hooks.json` from the trusted project configuration layer. The file contains the hook declarations and concise inline commands. There are no separate handler scripts.

### `Stop` hook

The `Stop` hook reads the standard input event, including `last_assistant_message` and `stop_hook_active`.

If the last message does not contain `章节状态：已完成`, the hook permits the turn to stop. It does not interfere with ordinary teaching pauses.

If the message declares completion, the hook checks:

1. the message contains a concrete chapter identifier;
2. the message names an existing `topics/<topic>/learning/log.md`;
3. the referenced log is not left staged or unstaged;
4. the latest lesson-closing commit includes the referenced log;
5. the synchronization line is either a truthful `已同步 <commit>` result or an explicit `待同步——<reason>` result;
6. `已同步` is inconsistent if the local branch is ahead of or diverged from its configured upstream;
7. `待同步` is accepted only when Git shows a local commit that has not reached the upstream, or another concrete repository blocker is visible.

When a check fails, the hook returns `decision: "block"` with one concise natural-language reason. Codex receives an automatic continuation turn and performs the missing closure step.

The hook must not loop indefinitely. After an actual push failure, Codex reports `待同步` with the exact error; that state is permitted to end the task. The hook never manufactures a successful synchronization claim.

### `SessionStart` hook

The `SessionStart` hook performs read-only Git inspection:

- unresolved merge or rebase state;
- modified learning records;
- local commits ahead of or diverged from the upstream.

If none exist, it adds no context. If a closure is pending, it injects a short instruction telling Codex to inspect and recover the previous lesson's logging or synchronization before starting another lesson. Git is the recovery state, so no auxiliary file is needed.

The hook does not automatically modify files, commit, pull, rebase, or push. Those operations remain visible Codex actions subject to the workspace's normal safety and proxy rules.

## Failure handling

| Condition | Required behavior |
| --- | --- |
| Learning evidence is incomplete | Keep the lesson in progress; do not write a completion entry. |
| Log was written but not committed | `Stop` blocks and requests a scoped commit. |
| Commit exists but push was not attempted | `Stop` blocks; Codex attempts synchronization. |
| Push fails due to network or authentication | Report `待同步` with the exact error and allow the task to end. |
| Push is rejected because the remote advanced | Report the divergence; do not force-push. Preserve local work and retry safely in the current or next session. |
| Next session sees pending commits or conflicts | `SessionStart` makes recovery the first task before new teaching. |
| No upstream is configured | Treat synchronization as pending and report the missing upstream. |
| Hook is untrusted or disabled | Warn that closure enforcement is unavailable; Skill and repository rules still apply but are not mechanically enforced. |

## Verification scenarios

Hook behavior is verified manually without adding a test script or CI workflow:

1. **Ordinary teaching pause:** a response without the completion block stops normally.
2. **False completion:** a completion block with no log update is blocked.
3. **Uncommitted log:** a correct log entry left uncommitted is blocked.
4. **Committed but unpushed:** a completion claim saying `已同步` while the branch is ahead is blocked.
5. **Successful closure:** a commit containing the log and already present at the upstream is allowed.
6. **External push failure:** a local closure commit plus `待同步——<reason>` is allowed to stop.
7. **Recovery:** a new session with the unpushed closure commit receives recovery context before teaching.
8. **Skill regression:** a new concept absent from the topic log is explained and checked before an exercise is assigned.
9. **CMake routing:** generator or preset lessons load the syntax reference; unrelated CMake lessons do not.

Testing uses temporary or deliberately scoped commits and restores no generated build artifacts. Hook definitions are reviewed through Codex's hook trust interface after creation or modification.

## Repository changes

Implementation is limited to:

- add `.codex/hooks.json`;
- refine root `AGENTS.md` lesson-closure authorization and retry rule;
- simplify `.agents/skills/learning-coach/SKILL.md`;
- simplify `.agents/skills/cmake-coach/SKILL.md`;
- keep the two existing CMake reference documents as the detailed source;
- remove duplicated generic closure language from topic rules where needed;
- add `.qtcreator/` to `.gitignore`.

No CI configuration, handler script, machine status file, generated learning prose, or auxiliary log is introduced.

## Deployment and trust

Project-local hooks are discovered after cloning, but Codex requires the user to review and trust non-managed command hooks. A changed hook definition receives a new hash and must be trusted again. This one-time review is a security boundary and is not bypassed.

The initial implementation is Windows-first because this learning work is primarily performed on the current Windows machine. The hook configuration may provide a concise non-Windows `command` alongside `commandWindows` only when it can express the same checks without adding a script dependency. Unsupported environments must fail visibly rather than silently claiming enforcement.

## Success criteria

- A trusted Codex session cannot normally claim a lesson is complete while its Markdown log is missing or uncommitted.
- A successful synchronization claim agrees with Git's configured upstream state.
- An external push failure is readable, durable in local Git state, and surfaced at the next session start.
- Ordinary teaching turns do not incur an extra continuation.
- The generic and CMake-specific Skills have one clear owner for each rule and no conflicting publication authorization.
- The repository remains understandable without reading Hook implementation details.
