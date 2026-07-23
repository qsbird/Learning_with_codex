# Learning Workspace

This repository is a home for project-based learning across tools, languages, and frameworks. Each topic keeps its own exercises and learning history so that its progress, validation commands, and domain-specific guidance stay together.

## Layout

```text
topics/
  <topic>/
    README.md          # purpose, entry points, and topic conventions
    AGENTS.md          # topic-only instructions
    learning/          # profile, roadmap, and evidence log
    exercises/         # small, focused practice projects
learning/
  _templates/          # starting point for a new topic's records
skills/
  learning-coach/      # reusable, topic-neutral coaching workflow
  <topic>-coach/       # optional domain-specific coaching skill
out/                   # ignored local build and generated output
```

Start with the topic index in [topics/README.md](topics/README.md). For a new subject, copy the record templates from `learning/_templates/`, add a topic README, and create a specialized skill only when the subject needs knowledge or workflow beyond `learning-coach`.

## Current topics

- [CMake](topics/cmake/README.md): target-based CMake, configuration, testing, packaging, and consumption.
