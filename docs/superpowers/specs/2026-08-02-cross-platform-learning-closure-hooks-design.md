# Cross-Platform Learning Closure Hooks Design

## Status and scope

This design supersedes only the platform-specific handler architecture in
`2026-08-02-learning-closure-hooks-design.md`. The previously approved teaching,
Markdown record, Git synchronization, completion-block, and no-CI decisions
remain in force.

The goal is identical enforcement on Windows, macOS, and Linux without copying
the lesson-closing policy into multiple platform scripts. Natural-language
guidance remains the source of intent; one small executable fixture verifies
the observable facts that prose alone cannot enforce.

## Constraints

- Codex currently executes only `type: "command"` Hook handlers. Parsed
  `prompt` and `agent` handlers cannot provide enforcement today.
- The repository may require Node.js, but it must not require npm packages,
  `package.json`, a package installation, CI, or network access.
- Git remains the durable synchronization state. Do not add a lesson state
  file, generated learning prose, or an auxiliary log.
- `topics/<topic>/learning/log.md` remains the lesson history and
  `roadmap.md` remains the stage overview.
- Project Hook discovery is automatic, but Codex's per-definition `/hooks`
  review and trust step remains mandatory on every machine. The repository
  must not bypass or conceal that security boundary.

## Chosen architecture

The implementation has three automation files:

1. `.codex/hooks.json` declares `SessionStart` and `Stop` and contains only
   short platform launchers.
2. `.codex/hooks/lesson-closure.mjs` is the single policy implementation used
   by every supported operating system.
3. `.codex/hooks/lesson-closure.test.mjs` uses Node's built-in test runner to
   protect the shared behavior.

Root `AGENTS.md` documents the Node.js prerequisite, local verification
command, and mandatory Hook trust checkpoint in natural language.

Node.js 18 or newer is the minimum execution environment. The handler uses
only stable built-in modules and must also work on newer maintained Node.js
releases. Git is already required by the repository.

### Platform launchers

`hooks.json` retains both Codex command fields:

- `command` uses the host's POSIX shell on macOS and Linux.
- `commandWindows` uses Windows PowerShell.

Each launcher performs only three jobs: verify that `node` is available,
resolve the Git repository root, and execute
`.codex/hooks/lesson-closure.mjs`. No lesson policy is duplicated in the
launchers.

If Node.js, Git, the repository root, or the handler cannot be resolved, the
launcher emits valid Hook JSON with `continue: false`, `stopReason`, and a
visible `systemMessage`. Missing prerequisites therefore fail closed instead
of silently disabling the gate.

## Handler responsibilities

The handler reads one JSON event from standard input and writes exactly one
JSON object to standard output. Diagnostics may go to standard error, but must
not corrupt standard output.

The module is split into small exported units:

- input parsing and event dispatch;
- a Git adapter that invokes `git` with argument arrays and no shell;
- completion-block parsing and path validation;
- `SessionStart` repository-state evaluation;
- `Stop` lesson-closure evaluation;
- Hook JSON output and fail-closed error conversion.

Production Git calls use `execFileSync` or an equivalent argument-array API.
No message text, file path, commit id, or Git output is concatenated into a
shell command.

### SessionStart

For `startup`, `resume`, `clear`, and `compact`, the handler checks:

- modified or untracked `topics/<topic>/learning/log.md` or `roadmap.md`;
- unresolved Git paths;
- missing configured upstream;
- a positive `@{upstream}..HEAD` commit count.

If any signal exists, it returns `hookSpecificOutput.additionalContext` with
the approved recovery instruction. Otherwise it returns `{}`. Unrelated IDE
or generated files do not trigger lesson recovery.

### Stop

The handler returns `{}` immediately unless `last_assistant_message` contains
the exact marker `章节状态：已完成`.

Once gated, it requires this structure:

```text
章节：<id>
章节状态：已完成
学习日志：已更新 topics/<topic>/learning/log.md
仓库同步：已同步 <commit>
```

After a real push failure, only the last line changes to:

```text
仓库同步：待同步——<exact reason>
```

The declared log path must use forward slashes and match exactly one topic
segment: `topics/<topic>/learning/log.md`. Absolute paths, backslashes, empty
topic names, extra path levels, and `.` or `..` segments are rejected before
filesystem access.

Checks then run in this order:

1. chapter id, log declaration, and one synchronization result are present;
2. the log exists below the repository root;
3. the log has no uncommitted change;
4. the latest commit includes that exact log path;
5. a synchronized claim names the current `HEAD` and the branch is not ahead
   of its upstream;
6. a pending claim is rejected when the configured upstream already contains
   `HEAD`.

The first failed check produces one natural-language reason. On the first
failure, `Stop` returns `decision: "block"`. When `stop_hook_active` is already
true, it returns `continue: false` with the failure reason and the existing
no-loop warning.

## Failure behavior

Unexpected failures are policy failures, not permission to proceed. Invalid
stdin JSON, an unsupported event shape, Git execution failure, insufficient
Node.js version, or an internal exception returns a common fail-closed object:

```json
{
  "continue": false,
  "stopReason": "<specific reason>",
  "systemMessage": "<specific reason>"
}
```

Expected policy failures continue to use the event-specific outputs described
above. Error text must identify the missing prerequisite or failed verification
without exposing credentials or full environment data.

An untrusted or disabled Hook remains outside the handler's control because
Codex skips it before execution. Root guidance therefore states that a new
lesson must not begin until `/hooks` shows the current project definition as
reviewed, trusted, and enabled. This is a documented security prerequisite,
not an automatically bypassed configuration step.

## Verification design

`lesson-closure.test.mjs` uses `node:test` and `node:assert/strict`; it installs
no dependencies.

Pure tests cover:

- ordinary messages bypassing `Stop`;
- every missing completion field;
- exact success and pending forms;
- commit-id comparison;
- path traversal and malformed log paths;
- first and second Stop failures;
- all four SessionStart recovery signals;
- fail-closed conversion for malformed input and Git errors.

Git integration tests create repositories only beneath an OS temporary
directory. They cover clean state, dirty learning records, conflicts where
practical, committed and uncommitted logs, latest-commit membership, missing
upstream, ahead commits, and synchronized state. Tests remove only the exact
temporary directory they created and never modify the learning workspace.

Launcher smoke tests execute the parsed Hook commands with synthetic stdin.
Windows verification covers `commandWindows`; macOS/Linux verification covers
`command`. On Windows, the POSIX launcher may additionally be exercised with
Git for Windows' shell when available, but that does not replace running the
same smoke test on a real macOS or Linux host.

The local regression command is:

```text
node --test .codex/hooks/lesson-closure.test.mjs
```

No CI workflow is added. A Hook change is publishable only after the tests,
JSON parsing, whitespace checks, direct launcher smoke test on the current
platform, `/hooks` trust review, and live ordinary/invalid Stop checks pass.

## Migration and acceptance

The current inline Windows implementation is replaced, not retained as a
fallback. Its approved Chinese messages and Git semantics move into the shared
module. The existing policy and Skill commits remain unchanged.

Acceptance requires:

- both Hook entries invoke the same tracked `.mjs` handler;
- no policy branch is implemented in a platform launcher;
- Node.js absence and internal errors fail closed;
- all built-in tests pass without network access or package installation;
- the current definition is reviewed and trusted through `/hooks`;
- live `SessionStart` recovery, ordinary Stop, invalid completion, and
  second-pass loop prevention behave as specified;
- documentation clearly states that every new machine needs Node.js and one
  explicit Hook trust review.

The remaining limitation is intentional: Codex administrators or users can
disable Hooks, and non-Codex Git operations do not run the Stop gate. The
repository can make these states visible and fail closed when its handler is
invoked, but it cannot override Codex's security and administration controls.
