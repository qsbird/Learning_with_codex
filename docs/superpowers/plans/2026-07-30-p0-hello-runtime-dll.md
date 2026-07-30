# p0-hello Runtime DLL Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the Windows CLion Debug build of `hello.exe` runnable without adding the sibling `src` output directory to `PATH`.

**Architecture:** `hello` already links the shared `greeting` target. Add a Windows-only post-build copy on `hello` so CMake copies the resolved runtime DLL from `$<TARGET_FILE:greeting>` into `$<TARGET_FILE_DIR:hello>`. Keep the MinGW runtime DLLs as a toolchain environment responsibility and restore the MinGW `bin` directory to the user PATH.

**Tech Stack:** CMake 3.10+, Ninja, MinGW-w64 bundled with CLion, PowerShell.

## Global Constraints

- Preserve `greeting` as a `SHARED` target.
- Do not hard-code `cmake-build-debug`, preset binary directories, or generator-specific output paths in CMake.
- Copy only the project runtime DLL during development builds; do not bundle MinGW runtime DLLs in the source tree.
- Verify the executable with MinGW `bin` on PATH but without the sibling `src` directory on PATH.

---

### Task 1: Copy the project DLL beside the executable

**Files:**
- Modify: `topics/cmake/exercises/p0-hello/app/CMakeLists.txt`
- Test: PowerShell runtime reproduction against `topics/cmake/exercises/p0-hello/cmake-build-debug/app/hello.exe`

**Interfaces:**
- Consumes: CMake targets `hello` and `greeting`; `$<TARGET_FILE:greeting>` resolves to the built runtime DLL.
- Produces: `libgreeting.dll` beside `$<TARGET_FILE:hello>` on Windows after the `hello` target links.

- [ ] **Step 1: Run the failing runtime reproduction**

Run from `topics/cmake/exercises/p0-hello`:

```powershell
$toolchainBin = 'C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin'
$runtimePath = "$toolchainBin;$env:Path"
$env:Path = $runtimePath
& '.\cmake-build-debug\app\hello.exe'
if ($LASTEXITCODE -ne -1073741515) {
    throw "Expected missing-DLL exit code, got $LASTEXITCODE"
}
```

Expected: `hello.exe` fails with `0xC0000135` because `libgreeting.dll` is only in the sibling `src` directory.

- [ ] **Step 2: Add the Windows post-build copy rule**

Append this block after `target_link_libraries(hello ...)` in `app/CMakeLists.txt`:

```cmake
if(WIN32)
    add_custom_command(TARGET hello POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "$<TARGET_FILE:greeting>"
                "$<TARGET_FILE_DIR:hello>"
    )
endif()
```

`TARGET hello POST_BUILD` attaches the command to the executable after it links. `$<TARGET_FILE:greeting>` and `$<TARGET_FILE_DIR:hello>` are generator expressions evaluated for the active generator and configuration.

- [ ] **Step 3: Reconfigure and build the CLion Debug tree**

Run from `topics/cmake/exercises/p0-hello`:

```powershell
$toolchainBin = 'C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin'
$env:Path = "$toolchainBin;$env:Path"
cmake -S . -B cmake-build-debug -G Ninja
cmake --build cmake-build-debug --verbose
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Test-Path '.\cmake-build-debug\app\libgreeting.dll'
```

Expected: build succeeds and `Test-Path` prints `True`.

- [ ] **Step 4: Verify the direct runtime path**

Run from `topics/cmake/exercises/p0-hello`:

```powershell
$toolchainBin = 'C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin'
$env:Path = "$toolchainBin;$env:Path"
& '.\cmake-build-debug\app\hello.exe'
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
```

Expected: the application prints its greeting and exits with code `0`; no `cmake-build-debug/src` path is added.

- [ ] **Step 5: Commit the CMake rule**

```powershell
git add topics/cmake/exercises/p0-hello/app/CMakeLists.txt
git commit -m "Fix hello shared DLL runtime path"
```

### Task 2: Restore the persistent MinGW toolchain runtime path

**Files:**
- Modify: Windows user environment variable `Path`
- Test: User-level Path query in PowerShell

**Interfaces:**
- Consumes: `C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin`, which contains `libstdc++-6.dll`, `libgcc_s_seh-1.dll`, and `libwinpthread-1.dll`.
- Produces: a user-level `Path` entry inherited by newly started CLion processes.

- [ ] **Step 1: Check the pre-change user PATH**

```powershell
[Environment]::GetEnvironmentVariable('Path', 'User') -split ';' |
    Where-Object { $_ -eq 'C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin' }
```

Expected: no output, proving the persistent toolchain path is missing.

- [ ] **Step 2: Add the missing directory exactly once**

```powershell
$toolchainBin = 'C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin'
$userPath = [Environment]::GetEnvironmentVariable('Path', 'User')
if (($userPath -split ';') -notcontains $toolchainBin) {
    [Environment]::SetEnvironmentVariable('Path', "$userPath;$toolchainBin", 'User')
}
```

- [ ] **Step 3: Verify persistence and restart CLion**

```powershell
[Environment]::GetEnvironmentVariable('Path', 'User') -split ';' |
    Where-Object { $_ -eq 'C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin' }
```

Expected: exactly one matching line. Fully close and restart CLion so its process inherits the new user environment.

- [ ] **Step 4: Commit repository changes only**

```powershell
git status --short
```

Expected: no environment state is staged; only repository files belong in a commit.
