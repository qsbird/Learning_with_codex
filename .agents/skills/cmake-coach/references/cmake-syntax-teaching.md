# Teaching CMake syntax before an exercise

Use this reference when the lesson introduces generators, build configurations, or `CMakePresets.json`. Present the relevant section before asking the learner to change a file.

## Generator and configuration timing

Start with the distinction the learner needs to use:

- A single-configuration generator creates one configuration in a build tree. Choose it while configuring, for example with `-DCMAKE_BUILD_TYPE=Debug` when the generator supports that variable.
- A multi-configuration generator can create Debug and Release outputs in one build tree. Select the configuration while building with `--config <name>`.

Show commands as a matched pair, then ask one prediction:

```powershell
# Multi-configuration example
cmake -S <source> -B <build> -G "Visual Studio 18 2026"
cmake --build <build> --config Debug
```

Explain that `-G` selects the generator during configuration, while `--config` selects one configuration from a tree that already supports several. Ask whether changing `--config` requires another configure step and why.

## Preset object anatomy

Explain a preset object before assigning it. This is a minimal configure preset that adds a Windows-only entry:

```json
{
  "name": "windows-default",
  "inherits": "default",
  "binaryDir": "${sourceDir}/out/build/windows-default",
  "condition": {
    "type": "equals",
    "lhs": "${hostSystemName}",
    "rhs": "Windows"
  }
}
```

Explain the parts in this order:

1. The object is one element of the top-level `configurePresets` array.
2. `name` is the command-line identifier used by `cmake --preset windows-default`.
3. `inherits` reuses values from `default`; this object only supplies differences.
4. `binaryDir` chooses an independent build tree. `${sourceDir}` expands to the directory containing the top-level CMake project.
5. `condition` controls whether this entry is available on the current host. `type: "equals"` compares the text on `lhs` and `rhs`; `${hostSystemName}` expands to the host system name.

State the boundary explicitly: a false condition hides the preset from the available list and prevents it from being selected. It does not itself choose a compiler, generator, cache variable, or build type.

Only after this explanation, ask for the learner's prediction about a non-Windows host and then assign the edit.

## Build preset relationship

A build preset selects an existing configure preset with `configurePreset`:

```json
{
  "name": "windows-default",
  "configurePreset": "windows-default"
}
```

Explain that this object belongs in `buildPresets`, and that its `configurePreset` value must name the configure entry whose build tree it will use. Ask the learner which field connects the two before asking them to create it.
