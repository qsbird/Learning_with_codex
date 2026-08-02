# Learning Closure Hooks Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add Codex lifecycle guardrails that prevent a verified lesson from being announced as complete without a committed Markdown learning record and an honest repository-sync result, while simplifying the generic and CMake-specific coaching Skills.

**Architecture:** Natural-language Markdown records remain the learning source of truth. `learning-coach` owns the generic teaching and closure contract, `cmake-coach` only routes CMake-specific context, and project-local `SessionStart`/`Stop` command hooks inspect Git plus the assistant's fixed completion block. Git itself represents pending synchronization; no CI, handler script, or machine state file is added.

**Tech Stack:** Markdown Agent Skills, repository `AGENTS.md`, Codex project hooks in JSON, inline Windows PowerShell, Git.

## Global Constraints

- Do not add GitHub Actions or another CI workflow.
- Do not add `.ps1`, `.bat`, Python, Node, or other standalone handler scripts.
- Do not add a machine-readable lesson state file, auxiliary log, or generated learning prose.
- Keep `topics/<topic>/learning/log.md` as the durable lesson history and `roadmap.md` as the stage overview.
- Permit a task to end after a real push failure only when the final response reports `仓库同步：待同步——<exact reason>`; the next session must surface the pending Git state before teaching.
- Project-local command hooks require review and trust after creation or modification; do not bypass this security boundary.
- Preserve unrelated working-tree changes and never stage IDE or generated output.

---

## File map

- Modify `AGENTS.md`: own standing lesson-closure authorization and retry policy.
- Modify `.gitignore`: ignore `.qtcreator/` directories at any topic depth.
- Modify `topics/cmake/AGENTS.md`: retain CMake-only project rules; remove duplicated generic closure language.
- Modify `topics/qt/AGENTS.md`: retain Qt-only project rules; remove duplicated generic closure language.
- Modify `.agents/skills/learning-coach/SKILL.md`: own the concise generic teaching and closure workflow.
- Modify `.agents/skills/cmake-coach/SKILL.md`: become a thin adapter that explicitly requires `learning-coach` and routes existing references.
- Create `.codex/hooks.json`: declare `SessionStart` recovery context and `Stop` completion enforcement using inline commands.
- Do not modify `.agents/skills/cmake-coach/references/cmake-track.md` or `cmake-syntax-teaching.md`; they already own the detailed CMake material.

### Task 1: Consolidate durable repository policy

**Files:**
- Modify: `AGENTS.md`
- Modify: `.gitignore`
- Modify: `topics/cmake/AGENTS.md`
- Modify: `topics/qt/AGENTS.md`

**Interfaces:**
- Consumes: existing Markdown log/roadmap locations and root end-of-session sync policy.
- Produces: one repository-level standing authorization and topic files containing only domain-specific constraints.

- [ ] **Step 1: Capture the current policy failures**

Run:

```powershell
rg -n "standing authorization|持续授权|待同步|下一次.*同步" AGENTS.md
git check-ignore topics/qt/exercises/p0-hello-widget/.qtcreator
rg -n "append|日志|roadmap" topics/cmake/AGENTS.md topics/qt/AGENTS.md
```

Expected before modification:

- the first command finds no standing authorization or retry rule;
- `git check-ignore` exits `1` because `.qtcreator/` is not ignored;
- both topic rule files contain generic log/roadmap closure requirements.

- [ ] **Step 2: Replace the root sync section with a lesson-closure contract**

Keep the existing workspace and verification sections. Replace `## End-of-session GitHub sync` with wording that states all of the following explicitly:

```md
## Verified lesson closure

When a lesson meets its stated exit evidence, this repository grants standing authorization to:

1. append the outcome, evidence, misconception, and next step to the active topic's `learning/log.md`;
2. update `learning/roadmap.md` only when a stage exit criterion is met;
3. inspect `git status` and stage only the active lesson's source, learning records, Skills, and relevant guidance;
4. create one Lore-protocol commit and push `main` to `origin`.

Do not request this authorization again. Do not create an empty commit or stage generated output, IDE state, `.DS_Store`, or `.omx/` state.

If synchronization fails, preserve the local commit and report `仓库同步：待同步——<exact reason>`. Before a later session begins a new lesson, inspect and recover any uncommitted learning record, conflict, or local commit not present at the configured upstream. Never force-push to resolve a lesson-closing conflict.
```

- [ ] **Step 3: Remove generic closure duplication from topic rules**

In `topics/cmake/AGENTS.md`, keep the exercise location, `out/cmake/`, target-based style, and CMake Coach routing. Retain only the CMake-specific roadmap constraint if needed; remove the repeated instruction to append the generic lesson log.

In `topics/qt/AGENTS.md`, keep standalone/project-mapping, read-only reference-project, Qt output, and unfamiliar Qt/CMake knowledge rules. Remove the generic final bullet that repeats log and roadmap closure.

- [ ] **Step 4: Ignore Qt Creator local state**

Add this line beside the other IDE exclusions in `.gitignore`:

```gitignore
.qtcreator/
```

- [ ] **Step 5: Verify the consolidated policy**

Run:

```powershell
rg -n "standing authorization|待同步|Never force-push" AGENTS.md
git check-ignore -v topics/qt/exercises/p0-hello-widget/.qtcreator
rg -n "append|日志|roadmap" topics/cmake/AGENTS.md topics/qt/AGENTS.md
git diff --check
```

Expected:

- root guidance contains authorization, pending-sync, and no-force-push rules;
- `.qtcreator/` resolves to the new `.gitignore` line;
- topic files contain no generic duplicate closure instruction;
- `git diff --check` exits `0`.

- [ ] **Step 6: Commit the policy consolidation**

```powershell
git add AGENTS.md .gitignore topics/cmake/AGENTS.md topics/qt/AGENTS.md
git commit -m "lore: consolidate verified lesson closure policy"
```

### Task 2: Simplify the generic learning Coach

**Files:**
- Modify: `.agents/skills/learning-coach/SKILL.md`
- Verify: `.agents/skills/learning-coach/agents/openai.yaml`

**Interfaces:**
- Consumes: topic README/profile/roadmap/log and root standing authorization.
- Produces: the sole generic contract for unfamiliar-knowledge teaching, practice, evidence, and lesson closure.

- [ ] **Step 1: Record the baseline duplication and consent conflict**

Run:

```powershell
$text=Get-Content -Raw -Encoding UTF8 .agents/skills/learning-coach/SKILL.md
($text | Measure-Object -Word -Line)
rg -n "explicit consent|Default to a short in-chat|Teach syntax|micro-concept|hint ladder|learning/log" .agents/skills/learning-coach/SKILL.md
```

Expected before modification: approximately 1765 words, multiple overlapping teaching sections, and a final rule requiring explicit consent before log edits, commits, or pushes.

- [ ] **Step 2: Rewrite the Skill around five compact contracts**

Keep the existing frontmatter name and a trigger-focused description. Use these sections and requirements:

```md
# Learning Coach

## Load the learning state

- Read repository and topic guidance, then the active topic's README, profile, roadmap, and log.
- Choose one session outcome from the learner's goal and recorded evidence.
- Treat readiness questions as diagnosis, not grading.

## Teach unfamiliar knowledge first

- Compare every required syntax, API, function, command, and concept with the roadmap and log.
- If positive evidence is absent or the learner is unsure, pause the task: explain the problem solved, show the smallest valid form in context, explain new tokens/scope/effect, then ask for one paraphrase or prediction and wait.
- Do not begin practice until the answer shows a workable model; repair only the specific gap when it does not.

## Run one learning loop

- Use one primary novelty, a familiar starting point, a visible result, and explicit exit evidence.
- Follow: activate/predict -> frame -> minimal model -> understanding check -> bounded practice -> verify -> explain or vary.
- Give practice as Goal, Starting point, Prerequisite evidence, New syntax, Mini example, Predict, Task, Verify, Explain.
- Use the least-helpful sufficient hint: question, concept, local location/prose edit, then narrow fragment.
- Do not silently implement the learner's exercise or provide a complete solution unless explicitly requested.

## Assess and adapt

- Completion requires independent practice plus a correct explanation or small transfer, not a passing command alone.
- Raise one difficulty dimension after independent success; keep level after one hint; reduce scope after repeated hints; remove tooling friction without treating it as a learning failure.
- For a learning path, each milestone names starting point, one hinge, practice, verification, exit evidence, review, and deferred topics.

## Close a verified lesson

- Append date, outcome, teaching, learner evidence, verification command/result, misconception, explanation, and next step to the active Markdown log.
- Update the roadmap only when its stage exit evidence is met.
- Under the repository's standing authorization, stage only scoped learning/source changes, create one Lore commit, attempt to push `main`, and never force-push.
- If the push fails externally, keep the local commit and report the exact pending reason; recover it before the next lesson.
- A successful final closure uses exactly:

  章节：<id>
  章节状态：已完成
  学习日志：已更新 topics/<topic>/learning/log.md
  仓库同步：已同步 <commit>

- After a real push failure, replace the last line with `仓库同步：待同步——<exact reason>`.
- If evidence or local record closure is incomplete, do not emit `章节状态：已完成`.

Material environment changes, installations, credentials, external communication, or changes outside the learning workspace still require confirmation.
```

Preserve the semantic requirements, but edit for smooth imperative prose rather than copying the outline mechanically. Do not reintroduce multiple overlapping templates.

- [ ] **Step 3: Check size, triggers, and retained guarantees**

Run:

```powershell
$text=Get-Content -Raw -Encoding UTF8 .agents/skills/learning-coach/SKILL.md
$measure=$text | Measure-Object -Word -Line
$measure
rg -n "unfamiliar|positive evidence|smallest valid|wait|independent|standing authorization|章节状态：已完成|待同步" .agents/skills/learning-coach/SKILL.md
rg -n "explicit consent|Default to a short in-chat" .agents/skills/learning-coach/SKILL.md
Get-Content -Raw -Encoding UTF8 .agents/skills/learning-coach/agents/openai.yaml
git diff --check
```

Expected:

- approximately 900-1100 words;
- all unfamiliar-knowledge, syntax-first, wait-for-understanding, evidence, and closure terms are present;
- the conflicting phrases are absent;
- `openai.yaml` still accurately describes a structured generic learning session;
- whitespace check passes.

- [ ] **Step 4: Commit the generic Skill simplification**

```powershell
git add .agents/skills/learning-coach/SKILL.md
git commit -m "lore: focus the generic learning coach"
```

### Task 3: Make the CMake Coach a thin adapter

**Files:**
- Modify: `.agents/skills/cmake-coach/SKILL.md`
- Verify unchanged: `.agents/skills/cmake-coach/references/cmake-track.md`
- Verify unchanged: `.agents/skills/cmake-coach/references/cmake-syntax-teaching.md`
- Verify: `.agents/skills/cmake-coach/agents/openai.yaml`

**Interfaces:**
- Consumes: the full `learning-coach` workflow and existing CMake references.
- Produces: only CMake topic loading, reference routing, and domain verification selection.

- [ ] **Step 1: Capture current duplication**

Run:

```powershell
$text=Get-Content -Raw -Encoding UTF8 .agents/skills/cmake-coach/SKILL.md
($text | Measure-Object -Word -Line)
rg -n "syntax-first|hint ladder|Record reproducible|Generators and configurations|Presets|Conditions|CMake defaults" .agents/skills/cmake-coach/SKILL.md
```

Expected before modification: approximately 431 words and matches for generic teaching/logging plus details already present in the two references.

- [ ] **Step 2: Replace the Skill body with explicit dependency and routing**

Keep the current frontmatter and use this body:

```md
# CMake Coach

**REQUIRED SUB-SKILL:** Use `learning-coach` for the complete teaching, practice, evidence, and verified lesson-closure workflow.

## Load the CMake topic

Read `topics/cmake/AGENTS.md`, `topics/cmake/README.md`, and its `learning/profile.md`, `roadmap.md`, and `log.md` before selecting work.

- When planning or revising the route, read `references/cmake-track.md`.
- When a lesson introduces generators, configurations, or `CMakePresets.json`, read `references/cmake-syntax-teaching.md` before teaching or assigning edits.

## Apply CMake evidence

- Begin from an existing exercise when practical and keep one primary CMake concept.
- Follow topic guidance for target-based design and isolated output under `out/cmake/`.
- Verify only the smallest behavior that proves the lesson: configure, build, executable run, or CTest.
- Record the exact command, observable result, and remaining misconception through the shared lesson-closure workflow.
```

- [ ] **Step 3: Verify thin-adapter boundaries**

Run:

```powershell
$text=Get-Content -Raw -Encoding UTF8 .agents/skills/cmake-coach/SKILL.md
$text | Measure-Object -Word -Line
rg -n "REQUIRED SUB-SKILL|cmake-track|cmake-syntax-teaching|configure|CTest" .agents/skills/cmake-coach/SKILL.md
rg -n "DirectConnection|condition.*lhs|hint ladder|push main|standing authorization" .agents/skills/cmake-coach/SKILL.md
git diff -- .agents/skills/cmake-coach/references
git diff --check
```

Expected:

- approximately 150-220 words;
- dependency, routing, and evidence terms are present;
- duplicated detailed teaching and publication terms are absent;
- both reference files have no diff.

- [ ] **Step 4: Commit the CMake adapter simplification**

```powershell
git add .agents/skills/cmake-coach/SKILL.md
git commit -m "lore: narrow the CMake coach to domain guidance"
```

### Task 4: Add Codex lesson-closure lifecycle hooks

**Files:**
- Create: `.codex/hooks.json`

**Interfaces:**
- Consumes from Codex: `SessionStart` common input; `Stop.last_assistant_message` and `Stop.stop_hook_active` through JSON on standard input.
- Consumes from repository: Git root, configured upstream, latest commit paths, and the fixed completion block.
- Produces to Codex: `{}` when no action is needed; `hookSpecificOutput.additionalContext` for recovery; `decision: "block"` plus a natural-language reason for incomplete closure.

- [ ] **Step 1: Confirm the hooks do not exist**

Run:

```powershell
Test-Path .codex/hooks.json
```

Expected before implementation: `False`.

- [ ] **Step 2: Create the Hook configuration**

Create `.codex/hooks.json` with:

- top-level description `Guard verified learning closure and surface pending Git synchronization.`;
- one `SessionStart` matcher for `startup|resume|clear|compact`;
- one `Stop` matcher group without a matcher, because Codex ignores matchers for `Stop`;
- `type: "command"`, a visible non-Windows warning command, and `commandWindows` implementations using `powershell.exe -NoProfile -Command`;
- `additionalContextLimit: 1200` on `SessionStart` and `timeout: 30` on `Stop`.

Use this exact non-Windows fallback for both handlers so unsupported hosts fail visibly without pretending enforcement succeeded:

```sh
printf '%s\n' '{"systemMessage":"Project lesson-closure enforcement requires Windows PowerShell and is unavailable on this host."}'
```

The `SessionStart` inline PowerShell must perform exactly this algorithm:

```powershell
$event = [Console]::In.ReadToEnd() | ConvertFrom-Json
$root = git rev-parse --show-toplevel 2>$null
if ($LASTEXITCODE -ne 0) { '{}'; exit 0 }

$status = @(git -C $root status --porcelain=v1)
$learningDirty = @($status | Where-Object {
    $_ -match 'topics[/\\][^/\\]+[/\\]learning[/\\](log|roadmap)\.md'
})
$conflicts = @(git -C $root diff --name-only --diff-filter=U)
$upstream = git -C $root rev-parse --abbrev-ref --symbolic-full-name '@{upstream}' 2>$null
$hasUpstream = $LASTEXITCODE -eq 0
$ahead = 0
if ($hasUpstream) {
    $ahead = [int](git -C $root rev-list --count '@{upstream}..HEAD')
}

if ($learningDirty.Count -gt 0 -or $conflicts.Count -gt 0 -or
    -not $hasUpstream -or $ahead -gt 0) {
    @{
        hookSpecificOutput = @{
            hookEventName = 'SessionStart'
            additionalContext = '上一次学习收尾可能尚未完成。开始新章节前，先检查学习日志、冲突、上游配置和未推送提交；恢复成功或报告准确阻塞后再教学。'
        }
    } | ConvertTo-Json -Compress -Depth 4
} else {
    '{}'
}
```

The `Stop` inline PowerShell must implement these exact checks in order:

```powershell
$event = [Console]::In.ReadToEnd() | ConvertFrom-Json
$message = [string]$event.last_assistant_message
if ($message -notmatch '章节状态：已完成') { '{}'; exit 0 }

$reason = $null
$chapter = [regex]::Match($message, '(?m)^章节：\s*(\S+)\s*$')
$logMatch = [regex]::Match(
    $message,
    '(?m)^学习日志：已更新\s+(topics/[^\r\n]+/learning/log\.md)\s*$'
)
$synced = [regex]::Match(
    $message,
    '(?m)^仓库同步：已同步\s+([0-9a-fA-F]{7,40})\s*$'
)
$pending = [regex]::Match(
    $message,
    '(?m)^仓库同步：待同步——(.+)\s*$'
)

if (-not $chapter.Success) { $reason = '章节完成声明缺少章节编号。' }
elseif (-not $logMatch.Success) { $reason = '章节完成声明缺少具体的 Markdown 学习日志路径。' }
elseif (-not $synced.Success -and -not $pending.Success) {
    $reason = '章节完成声明缺少明确的仓库同步结果。'
}

$root = git rev-parse --show-toplevel 2>$null
if (-not $reason -and $LASTEXITCODE -ne 0) { $reason = '当前目录不在 Git 仓库中，无法验证学习收尾。' }

if (-not $reason) {
    $logPath = $logMatch.Groups[1].Value
    if (-not (Test-Path -LiteralPath (Join-Path $root $logPath))) {
        $reason = "学习日志不存在：$logPath"
    } elseif (@(git -C $root status --porcelain=v1 -- $logPath).Count -gt 0) {
        $reason = "学习日志仍未提交：$logPath"
    } elseif (@(git -C $root diff-tree --no-commit-id --name-only -r HEAD) -notcontains $logPath) {
        $reason = '最新章节收尾提交没有包含声明的学习日志。'
    }
}

if (-not $reason) {
    $head = (git -C $root rev-parse --short HEAD).Trim()
    $upstream = git -C $root rev-parse --abbrev-ref --symbolic-full-name '@{upstream}' 2>$null
    $hasUpstream = $LASTEXITCODE -eq 0
    $ahead = 0
    if ($hasUpstream) {
        $ahead = [int](git -C $root rev-list --count '@{upstream}..HEAD')
    }

    if ($synced.Success) {
        $claimed = $synced.Groups[1].Value
        if (-not ($head.StartsWith($claimed) -or $claimed.StartsWith($head))) {
            $reason = "同步声明中的提交 $claimed 与当前 HEAD $head 不一致。"
        } elseif (-not $hasUpstream -or $ahead -gt 0) {
            $reason = '本地提交尚未到达配置的上游，不能声明已同步。'
        }
    } elseif ($pending.Success -and $hasUpstream -and $ahead -eq 0) {
        $reason = 'Git 未显示待推送提交，待同步声明与仓库状态不一致。'
    }
}

if ($reason -and $event.stop_hook_active) {
    @{
        continue = $false
        stopReason = $reason
        systemMessage = '章节收尾门禁第二次仍未通过。本次任务结束，但不得把该章节视为已完成；下一次会话必须先恢复收尾。'
    } | ConvertTo-Json -Compress
} elseif ($reason) {
    @{ decision = 'block'; reason = $reason } |
        ConvertTo-Json -Compress
} else {
    '{}'
}
```

Encode the two blocks as readable JSON command strings with escaped quotes and newlines; do not Base64-encode them. The non-Windows `command` must emit a valid JSON `systemMessage` stating that enforcement requires Windows PowerShell and is unavailable on that host.

- [ ] **Step 3: Validate JSON and required Hook fields**

Run:

```powershell
$hooks=Get-Content -Raw -Encoding UTF8 .codex/hooks.json | ConvertFrom-Json
$hooks.description
$hooks.hooks.SessionStart.Count
$hooks.hooks.Stop.Count
$hooks.hooks.SessionStart[0].hooks[0].commandWindows
$hooks.hooks.Stop[0].hooks[0].commandWindows
```

Expected: JSON parsing succeeds; description is present; both event counts are `1`; both Windows commands are non-empty and visibly use PowerShell.

- [ ] **Step 4: Review and trust the project Hook**

Open Codex's `/hooks` interface, confirm `.codex/hooks.json` is the only new project Hook source, review both commands, and trust the current definition hash. Do not use `--dangerously-bypass-hook-trust`.

- [ ] **Step 5: Verify the non-completion path**

Start or resume a Codex task in this repository and produce an ordinary teaching response without `章节状态：已完成`.

Expected: the response stops normally with no automatic continuation from the `Stop` hook.

- [ ] **Step 6: Verify missing-closure enforcement**

In a controlled Codex response, emit a completion block naming a nonexistent learning-log path.

Expected: `Stop` blocks once and continues Codex with `学习日志不存在：...`. The next response removes the false completion claim. If it repeats the invalid completion block, `stop_hook_active` makes the hook end the second continuation with a warning instead of looping indefinitely.

- [ ] **Step 7: Commit the Hook configuration**

```powershell
git add .codex/hooks.json
git commit -m "lore: guard verified lesson closure with Codex hooks"
```

### Task 5: Verify the integrated behavior and publish

**Files:**
- Verify: `AGENTS.md`
- Verify: `.agents/skills/learning-coach/SKILL.md`
- Verify: `.agents/skills/cmake-coach/SKILL.md`
- Verify: `.codex/hooks.json`
- Verify: `.gitignore`

**Interfaces:**
- Consumes: all outputs from Tasks 1-4.
- Produces: evidence that ordinary teaching is unaffected, false closure is blocked, pending synchronization is recoverable, and the scoped commits are published.

- [ ] **Step 1: Run repository consistency checks**

```powershell
git diff --check
git status --short
git check-ignore -v topics/qt/exercises/p0-hello-widget/.qtcreator
rg -n "explicit consent|Default to a short in-chat" .agents/skills
rg -n "章节状态：已完成|仓库同步：待同步" AGENTS.md .agents/skills/learning-coach/SKILL.md
git diff -- .agents/skills/cmake-coach/references
```

Expected:

- no whitespace errors;
- no uncommitted implementation files;
- Qt Creator state is ignored;
- conflicting consent wording is absent;
- the closure terms exist in root policy and generic Skill;
- CMake reference files are unchanged.

- [ ] **Step 2: Verify Skill size and responsibility boundaries**

```powershell
$generic=Get-Content -Raw -Encoding UTF8 .agents/skills/learning-coach/SKILL.md
$cmake=Get-Content -Raw -Encoding UTF8 .agents/skills/cmake-coach/SKILL.md
$generic | Measure-Object -Word -Line
$cmake | Measure-Object -Word -Line
rg -n "Generators and configurations|Preset object anatomy|condition.*lhs" .agents/skills/cmake-coach/SKILL.md
```

Expected: generic Skill is approximately 900-1100 words; CMake adapter is approximately 150-220 words; detailed generator/preset syntax is absent from the adapter.

- [ ] **Step 3: Verify a successful closure after the Hook commit is pushed**

Push the current commits using the repository proxy requirement:

```powershell
$env:HTTP_PROXY='http://127.0.0.1:10808'
$env:HTTPS_PROXY='http://127.0.0.1:10808'
$env:ALL_PROXY='http://127.0.0.1:10808'
$env:NO_PROXY='localhost,127.0.0.1,::1'
git push origin main
git status --short --branch
git rev-list --count '@{upstream}..HEAD'
```

Expected: push succeeds; branch is not ahead; ahead count is `0`.

- [ ] **Step 4: Verify next-session recovery without creating a state file**

Create no artificial learning commit. Instead, inspect the Hook definition and confirm its `SessionStart` condition covers each durable Git signal:

- dirty `topics/<topic>/learning/log.md` or `roadmap.md`;
- unresolved paths from `git diff --diff-filter=U`;
- missing upstream;
- positive `@{upstream}..HEAD` count.

Then use `/hooks` to confirm the trusted `SessionStart` handler remains enabled. Do not create or leave an unpushed test commit on `main` merely to exercise this path.

- [ ] **Step 5: Report implementation evidence**

The final implementation report must name:

- the Hook trust status;
- the ordinary-stop and false-completion test results;
- the before/after Skill word counts;
- the commit range pushed to `origin/main`;
- any remaining limitation, especially that non-Codex Git operations and disabled/untrusted Hooks are outside enforcement.
