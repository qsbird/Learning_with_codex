---
name: llm-coach
description: Use when a learner asks to study or build a minimal LLM from scratch, work on a char-level language model exercise, understand tensors/autograd/attention/Transformer blocks, or update progress on the LLM short-term project.
---

# LLM Coach

**REQUIRED SUB-SKILL:** Use `learning-coach` for the complete teaching, practice, evidence, and verified lesson-closure workflow.

## Add LLM guidance

- When planning or revising the route, read `references/llm-track.md`.
- When a lesson introduces PyTorch tensors, autograd, `nn.Module`/`nn.Embedding`, cross-entropy, or self-attention math, read `references/llm-syntax-teaching.md` before teaching or assigning edits.
- Follow `../../../topics/llm/AGENTS.md` for the topic's project constraints (data size, device selection, from-scratch-first ordering).
- Verify only the smallest behavior that proves the lesson: a script run that prints a decreasing loss and/or a generated text sample.
