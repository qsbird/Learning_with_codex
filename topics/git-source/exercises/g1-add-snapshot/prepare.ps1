param(
    [ValidatePattern('^[A-Za-z0-9][A-Za-z0-9_-]*$')]
    [string]$Name = 'g1-add-snapshot'
)

$ErrorActionPreference = 'Stop'
$workspacePath = (Resolve-Path (Join-Path $PSScriptRoot '../../../..')).Path
$labPath = Join-Path $workspacePath "out/git-source/$Name"

if (Test-Path -LiteralPath $labPath) {
    throw "Lab already exists: $labPath. Choose another -Name to preserve it."
}

New-Item -ItemType Directory -Path $labPath | Out-Null

# Keep every Git operation in this new lab and fail on native command errors.
function Invoke-LabGit {
    & git -C $labPath @args
    if ($LASTEXITCODE -ne 0) {
        throw "Git command failed with exit code ${LASTEXITCODE}: git $args"
    }
}

Invoke-LabGit init --template= --initial-branch=main --object-format=sha1
Invoke-LabGit config --local user.name 'Git Source Lab'
Invoke-LabGit config --local user.email 'git-source-lab@example.invalid'
Invoke-LabGit config --local commit.gpgSign false
Invoke-LabGit config --local core.autocrlf false
Invoke-LabGit config --local core.hooksPath .git/disabled-hooks

# Override global attributes for this one path so content stays unconverted.
$infoPath = Join-Path $labPath '.git/info'
New-Item -ItemType Directory -Path $infoPath | Out-Null
Set-Content -LiteralPath (Join-Path $infoPath 'attributes') -Encoding ascii `
    -Value 'note.txt -text -filter -ident -working-tree-encoding'

$notePath = Join-Path $labPath 'note.txt'
Set-Content -LiteralPath $notePath -Value 'A' -Encoding ascii
Invoke-LabGit add -- note.txt
Invoke-LabGit commit -m 'fixture: initial A'
Set-Content -LiteralPath $notePath -Value 'B' -Encoding ascii

Write-Output "Lab: $labPath"
Write-Output 'Ready: HEAD=A; index=A; working tree=B. Learner practice has not run.'
