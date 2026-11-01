#!/usr/bin/env python3
"""Compile only; check one specific deleted-operation diagnostic per probe."""
import argparse
from pathlib import Path
import re
import shutil
import subprocess
import sys

parser = argparse.ArgumentParser()
parser.add_argument("--probe-dir", type=Path, default=Path(__file__).resolve().parent)
args = parser.parse_args()
exercise = Path(__file__).resolve().parent.parent
compiler = shutil.which("c++")
if compiler is None:
    sys.exit("No c++ compiler found")
flags = [compiler, "-std=c++20", "-fsyntax-only", "-fno-color-diagnostics",
         "-I", str(exercise), "-I", str(exercise / "support")]
cases = [("control.cpp", None),
         ("construct.cpp", "call to deleted constructor"),
         ("assign.cpp", "overload resolution selected deleted operator '='")]
passed = True
for name, expected in cases:
    result = subprocess.run(flags + [str(args.probe_dir / name)],
                            capture_output=True, text=True)
    output = result.stdout + result.stderr
    errors = [line for line in output.splitlines()
              if re.search(r":\d+:\d+: (?:fatal )?error:", line)]
    if expected is None:
        ok = result.returncode == 0
    else:
        ok = result.returncode != 0 and len(errors) == 1 and expected in errors[0]
    print(f"{'PASS' if ok else 'FAIL'} {name}: compiler_exit={result.returncode}")
    if output:
        print(output.rstrip())
    if not ok and not output:
        print("Expected this operation to be rejected, but compilation succeeded.")
    passed = passed and ok
sys.exit(0 if passed else 1)
